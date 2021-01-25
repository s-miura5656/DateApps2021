#include "PlayerBase.h"
#include "../Data/MyAlgorithm.h"
#include "../Managers/SceneManager/SceneManager.h"
#include "../ParticleSystem/Particle.h"
#include "../Item/Itembase.hpp"
#include "../Managers/AudioManager/AudioManager.h"
#include "../Scenes/Main/Camera/MainCamera.h"
#pragma region 基本機能
PlayerBase::PlayerBase()
{

}

PlayerBase::~PlayerBase()
{

}

int PlayerBase::Update()
{
	auto pad = InputManager::Instance().GetGamePad(_tag);
	auto&& player_data = _i_player_data;

	ItemParameterTime();

	ParameterLevel();

	pad->Refresh();

	DebugControll();

	//! 死んでる時とそうでないときの判定
	if (_death_flag)
	{
		_respawn_time++;

		if (_respawn_time > RESPAWN_TIME)
		{
			player_data->SetHitPoint(_tag, RESPAWN_HITPOINT);
			player_data->SetState(_tag, PlayerEnum::Animation::WAIT);
			_respawn_time = 0;
			_death_flag = false;
			_move_flag  = false;
			auto respawnpos = IMapData::GetRespawnPosition(_tag);
			_transform.position = respawnpos;
			_index_num.x = respawnpos.x;
			_index_num.z = -respawnpos.z;
			player_data->SetIndexNum(_tag, _index_num);
			player_data->SetPosition(_tag, _transform.position);
			_i_player_data->SetParameter_PowerUp(_tag, false);
			_i_player_data->SetParameter_PowerDown(_tag, false);
		}
	}
	else
	{
		if (player_data->GetState(_tag) == PlayerEnum::Animation::DEATH)
		{
			DestroyArm();
			_death_flag      = true;
			AudioManager::Instance().ExplosionPlay();
			MainCamera::Instance().TimeReset();
			player_data->SetInvincibleMode(_tag, true);
			return 0;
		}
		else
		{
			InvincibleMode();
		}
		

		//! ダメージ状態の判定
		if (player_data->GetState(_tag) == PlayerEnum::Animation::DAMAGE)
		{
			_damage_hit_count++;
			_powerup_count = 9999;

			if (_damage_hit_count > DEATH_RIGOR)
			{
				player_data->SetState(_tag, PlayerEnum::Animation::DEATH);
				_damage_hit_count = 0;
			}

			DestroyArm();

			return 0;
		}
		
		//! パンチ発射状態ならすぐさまリターン
		if (player_data->GetState(_tag) == PlayerEnum::Animation::ATTACK)
		{
			player_data->SetIndexNum(_tag, _index_num);
			
			_arm->Update();

			return 0;
		}
		else if (player_data->GetState(_tag) == PlayerEnum::Animation::SHOT)
		{
			_shot_pending_count++;

			if (_shot_pending_count > player_data->GetShotRigorFrame(_tag))
			{
				player_data->SetState(_tag, PlayerEnum::Animation::ATTACK);
				player_data->SetPosition(_tag, _transform.position);
				_shot_pending_count = 0;
				CreateArm();
			}

			return 0;
		}
		else
		{
			DestroyArm();

			if (!_move_flag)
			{
				//! プレイヤー移動
				if (pad->Stick(STICK_INFO::LEFT_STICK) != STICK_CENTER)
				{
					InputAngle(pad);
					player_data->SetAngle(_tag, _transform.rotation.y);
					player_data->SetState(_tag, PlayerEnum::Animation::MOVE);
				}
				else
				{
					player_data->SetState(_tag, PlayerEnum::Animation::WAIT);
				}

				auto a = pad->Trigger(TRIGGER_INFO::LEFT_TRIGGER);

				//! ロケットパンチ発射切り替え
				if (pad->Button(BUTTON_INFO::BUTTON_B))
				{
					player_data->SetState(_tag, PlayerEnum::Animation::SHOT);
					player_data->SetPosition(_tag, _transform.position);
				}
			}
		}

		if (player_data->GetState(_tag) == PlayerEnum::Animation::MOVE)
		{
			InputMove(pad);
		}
	}

	if (_warp_flag)
	{
		if (_warp_other_pos != player_data->GetPosition(_tag))
		{
			Vector3 player_pos = player_data->GetPosition(_tag);
			_index_num.x = player_pos.x;
			_index_num.z = -player_pos.z;
			player_data->SetIndexNum(_tag, _index_num);
			_warp_flag = false;
		}
	}

	SetCollisionPosition();
	return 0;
}

void PlayerBase::Draw2D()
{
	if (_arm != nullptr)
		_arm->Draw2D();
}

void PlayerBase::Draw3D()
{
	//! 死んでる時とそうでないときの判定
	if (_death_flag)
	{
		_destroy_effect->SetPosition(_transform.position + Vector3_Up);
		_destroy_effect->PlayOneShot();
		_destroy_effect->Draw();
	}
	else
	{
		EffectDraw();

		_destroy_effect->Stop();
		
		ChangeAnimation();

		DrawModel();
		
		_hit_box->SetModelPosition();
		_hit_box->SetModelScale();
		
//		_hit_box->Draw3D();
		
		if (_arm != nullptr)
		{
			_arm->Draw3D();
		}
	}
}

void PlayerBase::DrawAlpha3D()
{
}
void PlayerBase::GetItem(ItemBase* item, string item_tag)
{
	auto effect = item->GetEffect();
	_status_tag = item_tag;
	if (_status_tag == ITEM_PLAYER_SPEEDUP)
	{
		AudioManager::Instance().PowerUpPlay();
	}
	else if (_status_tag == ITEM_ARM_SPEEDUP)
	{
		AudioManager::Instance().PowerUpPlay();
	}
	else if (_status_tag == ITEM_THUNDER)
	{
		AudioManager::Instance().ThunderPlay();
	}
	_i_player_data->SetStatusTag(_tag, _status_tag);
	_i_player_data->SetSpeed(_tag, effect._player_speed);
	_i_arm_Data->SetGoSpeed(_arm_tag, effect._arm_speed);
	_status_time = effect._effect_time;
	_powerup_count = 0;
}
#pragma endregion
void PlayerBase::Warp(Vector3 warppos)
{
	if (!_warp_flag)
	{
		auto&& player_data = _i_player_data;
		_transform.position = warppos;
		_index_num.x = warppos.x;
		_index_num.z = -warppos.z;
		player_data->SetIndexNum(_tag, _index_num);
		player_data->SetPosition(_tag, _transform.position);
		_warp_other_pos = warppos;
		_warp_flag = true;
	}
}
#pragma region 描画関係
//! @fn プレイヤーモデルの描画
void PlayerBase::DrawModel()
{
	//! モデルのパラメーターをセット
	_model->SetPosition(_transform.position);
	_model->SetRotation(Vector3(-15, _transform.rotation.y, 0));
	_model->SetMaterial(_model_material);

	//! シェーダー側に値をセット
	auto camera = SceneCamera::Instance().GetCamera();
	_shader->SetParameter("model_ambient", _model_material.Ambient);
	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetParameter("eye_pos", camera.GetPosition());

	Matrix vp = camera->GetViewProjectionMatrix();

	_shader->SetParameter("vp", vp);

	_model->SetScale(_transform.scale * 1.25);
	if (_i_player_data->GetState(_tag) != PlayerEnum::Animation::DAMAGE)
	{
		_shader->SetTechnique("FixAnimationModel");

		if (!_i_player_data->GetInvincibleMode(_tag))
		{
			_model->Draw(_shader);
		}
		else if(_invincible_count % 7 == 0)
		{
			_shader->SetTechnique("DamageAnimationModel");
			GraphicsDevice.BeginAlphaBlend();
			_model->Draw(_shader);
			GraphicsDevice.EndAlphaBlend();
		}
		else
		{
			GraphicsDevice.BeginAlphaBlend();
			_model->Draw(_shader);
			GraphicsDevice.EndAlphaBlend();
		}
	}
	else
	{
		_shader->SetTechnique("DamageAnimationModel");
		GraphicsDevice.BeginAlphaBlend();
		_model->Draw(_shader);
		GraphicsDevice.EndAlphaBlend();
	}

	_model->SetRotation(_transform.rotation);

	_i_player_data->SetAngle(_tag, _transform.rotation.y);
	_i_player_data->SetPosition(_tag, _transform.position);
	_model->SetScale(_transform.scale);

}

//! @fn プレイヤーモデルのアニメーション切り替え
void PlayerBase::ChangeAnimation()
{
	auto index = _i_player_data->GetState(_tag);

	_animation_count += GameTimer.GetElapsedSecond();

	//! 全てのアニメーショントラックを停止
	for (int i = 0; i < PlayerEnum::Animation::ANIMATION_ALL_TYPE; ++i)
	{
		_model->SetTrackEnable(i, FALSE);
	}

	//! アニメーショントラックと状態が違う場合アニメーショントラックを更新
	if (_animation_index != index)
	{
		_animation_index = index;
		_animation_count = 0;
	}

	//! アニメーショントラックのアニメーションを指定した位置から再生
	_model->SetTrackEnable(_animation_index, TRUE);	

	if (_animation_index == PlayerEnum::Animation::SHOT)
	{
		float shot_frame = 60.f / (float)_i_player_data->GetShotRigorFrame(_tag);
		_model->SetTrackPosition(_animation_index, _animation_count * shot_frame);
	}
	else if (_animation_index == PlayerEnum::Animation::MOVE)
	{
		_model->SetTrackPosition(_animation_index, _animation_count);
	}
	else
	{
		_model->SetTrackPosition(_animation_index, _animation_count);
	}
}
#pragma endregion

#pragma region 動作関係
//! @fn 移動処理
void PlayerBase::InputMove(BaseInput* pad)
{
	InputMoveDirection(pad);
	Move();
}

void PlayerBase::Move()
{
	if (!_move_flag)
		return;

	auto&& player_data = _i_player_data;

	_transform.position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
	_lerp_count += player_data->GetSpeed(_tag);
	_lerp_count = Clamp(_lerp_count, 0, 1);

	if (_lerp_count >= _moving_completion_end_value)
	{
		_move_flag  = false;
		_lerp_count = 0;
		player_data->SetPosition(_tag, _transform.position);
	}
}

void PlayerBase::InputMoveDirection(BaseInput* pad)
{
	if (_move_flag)
		return;

	auto&& map_data = _i_map_data->GetData();
	auto&& player_data = _i_player_data;

	auto pad_x = pad->Stick(STICK_INFO::LEFT_STICK).x;
	auto pad_y = pad->Stick(STICK_INFO::LEFT_STICK).y;

	float abs_x = fabsf(pad_x);
	float abs_z = fabsf(pad_y);

	int old_index_x = _index_num.x;
	int old_index_z = _index_num.z;

	if (abs_x > abs_z) 
	{
		std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).x) ? _index_num.x-- : _index_num.x++;
		_index_num.x = (int)Clamp(_index_num.x, 0, map_data[_index_num.z].size() - 1);
	}
	else if (abs_x < abs_z) 
	{
		std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).y) ? _index_num.z++ : _index_num.z--;
		_index_num.z = (int)Clamp(_index_num.z, 0, map_data.size() - 1);
	}

	if (map_data[_index_num.z][_index_num.x] != 'i' &&
		map_data[_index_num.z][_index_num.x] != 'w' &&
		map_data[_index_num.z][_index_num.x] != 'b' &&
		map_data[_index_num.z][_index_num.x] != 'd' &&
		map_data[_index_num.z][_index_num.x] != 's')
	{
		_new_pos = Vector3_Right * _index_num.x + Vector3_Forward * -_index_num.z;
		player_data->SetIndexNum(_tag, _index_num);
		_move_flag = true;
	}
	else
	{
		_index_num.x = old_index_x;
		_index_num.z = old_index_z;
	}

	_old_pos = _transform.position;
}

//! @fn 方向の入力
void PlayerBase::InputAngle(BaseInput* pad)
{
	_transform.rotation.y = AngleCalculating(pad->Stick(STICK_INFO::LEFT_STICK).x, pad->Stick(STICK_INFO::LEFT_STICK).y);
	_transform.rotation.y = AngleClamp(_transform.rotation.y);

	if (_transform.rotation.y != _old_angle)
	{
		_old_angle = _transform.rotation.y;
	}
}
#pragma endregion

#pragma region 当たり判定
//! @fn 当たり判定の座標設定
void PlayerBase::SetCollisionPosition()
{
	auto collision_pos = _transform.position;
	collision_pos.y += _model->GetScale().y / 2;
	_hit_box->SetHitBoxPosition(collision_pos);
}
#pragma endregion

#pragma region Arm関連
//! fn アームの生成
void PlayerBase::CreateArm()
{
	AudioManager::Instance().PunchShotPlay();
	_arm.reset();
	_arm = nullptr;

	_arm.reset(new Arm(_tag));
	_arm->Initialize();
}

//! @fn アームの破壊
void PlayerBase::DestroyArm()
{
	_arm.reset();
	_arm = nullptr;
}
#pragma endregion

#pragma region デバッグ関係
//! @fn デバッグ用パラメーター調整
void PlayerBase::DebugControll()
{
	KeyboardBuffer keybuffer = Keyboard->GetBuffer();
	KeyboardState keystate   = Keyboard->GetState();


	//! アームの飛ぶ速度調整
	float speed = _i_arm_Data->GetGoSpeed(_arm_tag);

	if (keybuffer.IsPressed(Keys_Up) && keystate.IsKeyDown(Keys_LeftControl))
		speed += 0.01f;

	if (keybuffer.IsPressed(Keys_Down) && keystate.IsKeyDown(Keys_LeftControl))
		speed -= 0.01f;

	speed = Clamp(speed, 0.01f, 10.0f);
	_i_arm_Data->SetGoSpeed(_arm_tag, speed);


	//! アームの戻る速度調整
	speed = _i_arm_Data->GetReturnSpeed(_arm_tag);

	if (keybuffer.IsPressed(Keys_Up) && keystate.IsKeyDown(Keys_LeftAlt))
		speed += 0.01f;

	if (keybuffer.IsPressed(Keys_Down) && keystate.IsKeyDown(Keys_LeftAlt))
		speed -= 0.01f;

	speed = Clamp(speed, 0.01f, 10.0f);
	_i_arm_Data->SetReturnSpeed(_arm_tag, speed);


	//! プレイヤーの移動速度調整
	speed = _i_player_data->GetSpeed(_tag);

	if (keybuffer.IsPressed(Keys_Up) && keystate.IsKeyDown(Keys_LeftShift))
		speed += 0.01f;

	if (keybuffer.IsPressed(Keys_Down) && keystate.IsKeyDown(Keys_LeftShift))
		speed -= 0.01f;

	speed = Clamp(speed, 0.01f, 10.0f);
	_i_player_data->SetSpeed(_tag, speed);


	//! アームの限界距離
	int range = _i_arm_Data->GetLimitRange(_arm_tag);

	if (keybuffer.IsPressed(Keys_Right))
		range++;

	if (keybuffer.IsPressed(Keys_Left))
		range--;

	range = (int)Clamp(range, 1, 20);

	_i_arm_Data->SetLimitRange(_arm_tag, range);
}
void PlayerBase::ParameterLevel()
{
}

void PlayerBase::InvincibleMode()
{
	if (!_i_player_data->GetInvincibleMode(_tag))
		return;

	_invincible_count++;

	if (_invincible_count >= INVINCIBLE_FRAME)
	{
		_invincible_count = 0;
		_i_player_data->SetInvincibleMode(_tag, false);
	}
	
}

void PlayerBase::ItemParameterTime()
{
	if (_powerup_count >= _status_time)
	{
		_i_player_data->SetSpeed(_tag, 0.05f);
		_i_arm_Data->SetGoSpeed(_arm_tag, 0.1f);
		_status_tag = "";
		_i_player_data->SetStatusTag(_tag, _status_tag);
	}
	else
	{
		_powerup_count++;
	}
}

void PlayerBase::EffectDraw()
{
	if (_status_tag != _status_old)
	{
		if (_status_old != "")
		{
			for (auto&& effect : _effect)
			{
				_effect.at(_status_old)->Stop();
			}
		}
		_status_old = _status_tag;
	}

	if (_status_tag == "")
		return;
	
	_effect.at(_status_tag)->SetPosition(_transform.position + Vector3_Up);
	if(_status_tag == ITEM_ARM_SPEEDUP)
		_effect.at(_status_tag)->SetPosition(_transform.position + Vector3(0,0.5,0));
	_effect.at(_status_tag)->SetRotation(Vector3(-15, 0, 0));
	_effect.at(_status_tag)->PlayOneShot();
	_effect.at(_status_tag)->Draw();
}
