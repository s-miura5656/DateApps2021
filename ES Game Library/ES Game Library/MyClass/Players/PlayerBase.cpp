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

	if (_warp_flag && _move_flag && player_data->GetState(_tag) == PlayerEnum::Animation::WAIT)
	{
		_warp_time++;
		_warp_pos += 0.05;
		if (_warp_pos >= 0)
		{
			_warp_pos = 0;
		}
		if (_warp_time >= 60)
		{
			_warp_time = 0;
			_warp_pos = -1;
			_move_flag = false;
		}
	}
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

		}
	}
	else
	{
		if (player_data->GetState(_tag) == PlayerEnum::Animation::DEATH)
		{
			DestroyArm();
			_death_flag = true;
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
			if (pad->Stick(STICK_INFO::LEFT_STICK) != STICK_CENTER)
			{
				InputAngle(pad);
				player_data->SetAngle(_tag, _transform.rotation.y);
			}
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
					//player_data->SetAngle(_tag, _transform.rotation.y);
					player_data->SetState(_tag, PlayerEnum::Animation::MOVE);
				}
				else
				{
					player_data->SetState(_tag, PlayerEnum::Animation::WAIT);
				}

				auto a = pad->Trigger(TRIGGER_INFO::LEFT_TRIGGER);

				//! ロケットパンチ発射切り替え
				if (pad->ButtonDown(BUTTON_INFO::BUTTON_B))
				{
					auto mapdata = _i_map_data->GetData();
					auto index   = _i_player_data->GetIndexNum(_tag);
					while (true)
					{
						if (player_data->GetAngle(_tag) == 90)
						{
							if (mapdata[index.z][index.x + 1] == 'i' || mapdata[index.z][index.x + 1] == 'w')
							{
								break;
							}
						}
						else if (player_data->GetAngle(_tag) == 270)
						{
							if (mapdata[index.z][index.x - 1] == 'i' || mapdata[index.z][index.x - 1] == 'w')
							{
								break;
							}
						}
						else if (player_data->GetAngle(_tag) == 180)
						{
							if (mapdata[index.z + 1][index.x] == 'i' || mapdata[index.z + 1][index.x] == 'w')
							{
								break;
							}
						}
						else if (player_data->GetAngle(_tag) == 0)
						{
							if (mapdata[index.z - 1][index.x] == 'i' || mapdata[index.z - 1][index.x] == 'w')
							{
								break;
							}
						}
						player_data->SetState(_tag, PlayerEnum::Animation::SHOT);
						player_data->SetPosition(_tag, _transform.position);
						break;
					}
				}
			}
		}

		if (player_data->GetState(_tag) == PlayerEnum::Animation::MOVE)
		{
			InputMove(pad);
			if (pad->ButtonDown(BUTTON_INFO::BUTTON_B))
			{
				_move_punch = true;
			}
		}

		if (_warp_other_pos == player_data->GetPosition(_tag))
		{
			_transform.position = _warp_other_pos;
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
		_respawn_effect->SetPosition(IMapData::GetRespawnPosition(_tag) + Vector3_Up);
		_respawn_effect->SetRotation(Vector3(-15, 0, 0));
		_respawn_effect->PlayOneShot();
		_respawn_effect->Draw();
	}
	else
	{
		if (_warp_flag && _warp_other_pos != Vector3_Zero)
		{
			_warp_effect->Draw();
		}
		else
		{
			_warp_effect->Stop();
		}
		EffectDraw();

		_destroy_effect->Stop();
		_respawn_effect->Stop();
		ChangeAnimation();

		DrawModel();
		
		_hit_box->SetModelPosition();
		_hit_box->SetModelScale();
		
//		_hit_box->Draw3D();
		//if (_i_player_data->GetState(_tag) == PlayerEnum::Animation::ATTACK)
		//{
		//	_smoke_effect->SetPosition(_transform.position + Vector3_Up);
		//	_smoke_effect->SetRotation(Vector3(15, 0, 0));
		//	_smoke_effect->PlayOneShot();
		//	_smoke_effect->Draw();
		//}
		//else
		//{
		//	_smoke_effect->Stop();
		//}
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
	if (!_warp_flag && _transform.position != _warp_other_pos)
	{
		auto&& player_data = _i_player_data;
		_transform.position = warppos;
		_index_num.x = warppos.x;
		_index_num.z = -warppos.z;
		player_data->SetState(_tag, PlayerEnum::Animation::WAIT);
		player_data->SetIndexNum(_tag, _index_num);
		player_data->SetPosition(_tag, _transform.position);
		_warp_other_pos = warppos;
		_warp_flag = true;
		_move_flag = true;
		_warp_effect->SetPosition(_transform.position + Vector3_Up);
		_warp_effect->SetRotation(Vector3(-15, 0, 0));
		_warp_effect->PlayOneShot();
		AudioManager::Instance().WarpPlay();
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
			if (_warp_flag && _move_flag && _transform.position == _warp_other_pos)
			{
				auto pos = _transform.position;
				pos.y = _warp_pos;
				_model->SetPosition(pos);
				_model->Rotation(Vector3(0, _warp_pos * 300, 0));
			}
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

	//_i_player_data->SetAngle(_tag, _transform.rotation.y);
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

	_warp_other_pos = Vector3_Zero;
	auto&& player_data = _i_player_data;

	_transform.position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
	_lerp_count += player_data->GetSpeed(_tag);
	_lerp_count = Clamp(_lerp_count, 0, 1);

	if (_lerp_count >= _moving_completion_end_value)
	{
		_move_flag  = false;
		_lerp_count = 0;
		player_data->SetPosition(_tag, _transform.position);
		if (_warp_flag)
			_warp_flag = false;
		if (_move_punch)
		{
			player_data->SetState(_tag, PlayerEnum::Animation::SHOT);
			_move_punch = false;
		}
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


	// 軸の倒れている方向を決定する
	// 1.上下と左右の割合が1/3未満は斜めとみなさない
	if (abs_x / abs_z < 0.333333f || abs_z / abs_x < 0.333333f)
	{
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
	}
	// 斜めに倒されている
	else
	{
		// 進行方向ではない軸の方向に行けるか調べる
		const int angle = (int)_i_player_data->GetAngle(_tag);
		if (angle % 180 == 0)
		{
			// 前後を向いているので、左右を調べる
			std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).x) ? _index_num.x-- : _index_num.x++;
			_index_num.x = (int)Clamp(_index_num.x, 0, map_data[_index_num.z].size() - 1);
			if (map_data[_index_num.z][_index_num.x] == 'i' ||
				map_data[_index_num.z][_index_num.x] == 'w' ||
				map_data[_index_num.z][_index_num.x] == 'b' ||
				map_data[_index_num.z][_index_num.x] == 'd' ||
				map_data[_index_num.z][_index_num.x] == 's')
			{
				_index_num.x = old_index_x;
				_index_num.z = old_index_z;

				std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).y) ? _index_num.z++ : _index_num.z--;
				_index_num.z = (int)Clamp(_index_num.z, 0, map_data.size() - 1);
			}

		}
		else
		{
			// 左右を向いているので、前後を調べる
			std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).y) ? _index_num.z++ : _index_num.z--;
			_index_num.z = (int)Clamp(_index_num.z, 0, map_data.size() - 1);
			if (map_data[_index_num.z][_index_num.x] == 'i' ||
				map_data[_index_num.z][_index_num.x] == 'w' ||
				map_data[_index_num.z][_index_num.x] == 'b' ||
				map_data[_index_num.z][_index_num.x] == 'd' ||
				map_data[_index_num.z][_index_num.x] == 's')
			{
				_index_num.x = old_index_x;
				_index_num.z = old_index_z;

				std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).x) ? _index_num.x-- : _index_num.x++;
				_index_num.x = (int)Clamp(_index_num.x, 0, map_data[_index_num.z].size() - 1);
			}

		}
	}

	//if (abs_x > abs_z) 
	//{
	//	std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).x) ? _index_num.x-- : _index_num.x++;
	//	_index_num.x = (int)Clamp(_index_num.x, 0, map_data[_index_num.z].size() - 1);
	//}
	//else if (abs_x < abs_z) 
	//{
	//	std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).y) ? _index_num.z++ : _index_num.z--;
	//	_index_num.z = (int)Clamp(_index_num.z, 0, map_data.size() - 1);
	//}
	if (_index_num.x > old_index_x)
	{
		player_data->SetAngle(_tag, FrontAngle::RIGHT);
		_transform.rotation.y = FrontAngle::RIGHT;
	}
	else if (_index_num.x < old_index_x)
	{
		player_data->SetAngle(_tag, FrontAngle::LEFT);
		_transform.rotation.y = FrontAngle::LEFT;
	}
	else if (_index_num.z > old_index_z)
	{
		player_data->SetAngle(_tag, FrontAngle::FRONT);
		_transform.rotation.y = FrontAngle::FRONT;
	}
	else if (_index_num.z < old_index_z)
	{
		player_data->SetAngle(_tag, FrontAngle::BACK);
		_transform.rotation.y = FrontAngle::BACK;

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
	KeyboardState  keystate   = Keyboard->GetState();


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
	
	_effect.at(_status_tag)->SetPosition(_transform.position);
	if(_status_tag == ITEM_ARM_SPEEDUP)
		_effect.at(_status_tag)->SetPosition(_transform.position + Vector3(0,0.5,0));
	if (_status_tag == ITEM_THUNDER)
		_effect.at(_status_tag)->SetPosition(_transform.position + Vector3(0,1,0));
	_effect.at(_status_tag)->SetRotation(Vector3(-15, 0, 0));
	_effect.at(_status_tag)->PlayOneShot();
	if (_warp_flag && _move_flag)
		_effect.at(_status_tag)->SetPosition(_transform.position + Vector3(0, 9999, 0));
	_effect.at(_status_tag)->Draw();
}
