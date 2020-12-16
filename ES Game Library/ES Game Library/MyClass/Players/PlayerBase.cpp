#include "PlayerBase.h"
#include "../Data/MyAlgorithm.h"
#include "../Managers/SceneManager/SceneManager.h"
#include "../ParticleSystem/Particle.h"

PlayerBase::PlayerBase()
{

}

PlayerBase::~PlayerBase()
{

}

int PlayerBase::Update()
{
	auto pad = ControllerManager::Instance().GetController(_tag);
	pad->GamePadRefresh();

	DebugControll();

	//! 死んでる時とそうでないときの判定
	if (_death_flag)
	{
		_respawn_time++;

		if (_respawn_time > 120)
		{
			_i_player_data->SetHitPoint(_tag, 1000);
			_i_player_data->SetState(_tag, PlayerEnum::Animation::WAIT);
			_respawn_time = 0;
			_death_flag = false;
			_move_flag = false;
			_transform.position = _new_pos;
		}
	}
	else
	{
		if (_i_player_data->GetState(_tag) == PlayerEnum::Animation::DEATH)
		{
			_death_flag = true;
			DestroyArm();
			return 0;
		}

		//! ダメージ状態の判定
		if (_i_player_data->GetState(_tag) == PlayerEnum::Animation::DAMAGE)
		{
			_damage_hit_count++;

			if (_damage_hit_count > 30)
			{
				_i_player_data->SetState(_tag, PlayerEnum::Animation::DEATH);
				_damage_hit_count = 0;
			}

			DestroyArm();

			return 0;
		}

		//! 移動中か待機中か判定
		if (!_move_flag)
		{
			//! パンチ発射状態ならすぐさまリターン
			if (_i_player_data->GetState(_tag) == PlayerEnum::Animation::ATTACK)
			{
				_i_player_data->SetIndexNum(_tag, _index_num);
				
				_arm->Update();

				return 0;
			}
			else if (_i_player_data->GetState(_tag) == PlayerEnum::Animation::SHOT)
			{
				_shot_pending_count++;

				if (_shot_pending_count > 30)
				{
					_i_player_data->SetState(_tag, PlayerEnum::Animation::ATTACK);
					_i_player_data->SetPosition(_tag, _transform.position);
					_shot_pending_count = 0;
					CreateArm();
				}

				return 0;
			}
			else
			{
				DestroyArm();

				//! プレイヤー移動
				if (pad->GetPadStateX() != Axis_Center || pad->GetPadStateY() != Axis_Center)
				{
					_transform.rotation.y = AngleCalculating(pad->GetPadStateX(), pad->GetPadStateY());
					_transform.rotation.y = AngleClamp(_transform.rotation.y);
					_i_player_data->SetState(_tag, PlayerEnum::Animation::MOVE);
				}
				else
				{
					_i_player_data->SetState(_tag, PlayerEnum::Animation::WAIT);
				}

				//! ロケットパンチ発射切り替え
				if (pad->GetButtonState(GamePad_Button2))
				{
					_i_player_data->SetState(_tag, PlayerEnum::Animation::SHOT);
					_i_player_data->SetPosition(_tag, _transform.position);
				}
			}
		}

		if (_i_player_data->GetState(_tag) == PlayerEnum::Animation::MOVE)
		{
			//! 移動
			Move(pad);
		}
	}

	SetCollisionPosition();

	return 0;
}

void PlayerBase::Draw2D()
{
	if (_tag == "Player_1")
	{
//		SpriteBatch.DrawString(_font, Vector2(0, 180), Color(1.f, 1.f, 1.f), _T("プレイヤーの所持ポイント:%d"), _i_player_data->GetRankingPoint(_tag));
//		SpriteBatch.DrawString(_font, Vector2(0, 200), Color(1.f, 1.f, 1.f), _T("プレイヤーのHP:%d"), _i_player_data->GetHitPoint(_tag));
//		SpriteBatch.DrawString(_font, Vector2(0, 220), Color(1.f, 1.f, 1.f), _T("プレイヤーの移動速度:%f"), _i_player_data->GetSpeed(_tag));
	}

	if (_arm_tag == "Arm_1")
	{
//		SpriteBatch.DrawString(_font, Vector2(0, 240), Color(1.f, 1.f, 1.f), _T("アームの飛ぶ速度:%f"), _i_arm_Data->GetGoSpeed(_arm_tag));
//		SpriteBatch.DrawString(_font, Vector2(0, 260), Color(1.f, 1.f, 1.f), _T("アームの戻る速度:%f"), _i_arm_Data->GetReturnSpeed(_arm_tag));
//		SpriteBatch.DrawString(_font, Vector2(0, 280), Color(1.f, 1.f, 1.f), _T("アームの最大距離:%d"), _i_arm_Data->GetLimitRange(_arm_tag));
	}

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
	}
	else
	{
		_destroy_effect->Stop();
		
		ChangeAnimation();

		DrawModel();
		
		_hit_box->SetModelPosition();
		_hit_box->SetModelScale();
//		_hit_box->Draw3D();
		
		if (_arm != nullptr)
		{
			_arm->Draw3D();

			DrawWireModel();
		}
	}
}

void PlayerBase::DrawAlpha3D()
{
}

//! @fn プレイヤーモデルの描画
void PlayerBase::DrawModel()
{
	//! モデルのパラメーターをセット
	_model->SetPosition(_transform.position);
	_model->SetRotation(Vector3(0, _transform.rotation.y - 180, 0));
	_model->SetMaterial(_model_material);

	//! シェーダー側に値をセット
	auto camera = SceneCamera::Instance().GetCamera();
	_shader->SetParameter("model_ambient", _model_material.Ambient);
	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetParameter("eye_pos", camera.GetPosition());

	Matrix vp = camera->GetViewProjectionMatrix();
	_shader->SetParameter("vp", vp);

	if (_i_player_data->GetState(_tag) != PlayerEnum::Animation::DAMAGE)
	{
		_shader->SetTechnique("FixAnimationModel");
		_model->Draw(_shader);
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
}

//! @fn ワイヤーモデルの描画
void PlayerBase::DrawWireModel()
{
	auto camera = SceneCamera::Instance().GetCamera();

	_wire_shader->SetTexture("m_Texture", *_wire_texture);
	_wire_shader->SetParameter("model_ambient", _model_material.Ambient);
	_wire_shader->SetParameter("eye_pos", camera.GetPosition());
	
	Matrix vp = camera->GetViewProjectionMatrix();

	for (auto&& model : _wire_models)
	{
		model->SetMaterial(_model_material);
	}

	auto arm_positions = _i_arm_Data->GetAnglePositions(_arm_tag);
	auto arm_angles    = _i_arm_Data->GetAngles(_arm_tag);

	for (int i = 0; i < arm_positions.size(); ++i)
	{
		_wire_models[i]->SetPosition(arm_positions[i]);
		_wire_models[i]->SetRotation(Vector3(0, arm_angles[i] + 180, 0));
		Matrix world = _wire_models[i]->GetWorldMatrix();
		_wire_shader->SetParameter("wvp", world * vp);

		if (arm_positions.size() > _i_arm_Data->GetLimitRange(_tag) - 3)
		{
			_wire_shader->SetParameter("limit_color", Vector3(1.0f, 0.0f, 0.0f));
			_wire_shader->SetTechnique("FixLimitModel_S1");
			_wire_models[i]->Draw(_wire_shader);
		}
		else if (arm_positions.size() > _i_arm_Data->GetLimitRange(_tag) - 10)
		{
			_wire_shader->SetParameter("limit_color", Vector3(1.0f, 1.0f, 0.0f));
			_wire_shader->SetTechnique("FixLimitModel_S1");
			_wire_models[i]->Draw(_wire_shader);
		}
		else
		{
			_wire_shader->SetParameter("limit_color", Vector3(0.0f, 1.0f, 0.0f));
			_wire_shader->SetTechnique("FixLimitModel_S1");
			_wire_models[i]->Draw(_wire_shader);
		}
	}
}

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

	if (_animation_index != PlayerEnum::Animation::SHOT)
	{
		_model->SetTrackPosition(_animation_index, _animation_count);
	}
	else
	{
		_model->SetTrackPosition(_animation_index, _animation_count * 2.0f);
	}
}

//! @fn 移動処理
void PlayerBase::Move(Controller* pad)
{
	auto&& map_data = _i_map_data->GetData();

	//! 移動中か入力受付状態か判定
	if (_move_flag)
	{
		_transform.position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
		_lerp_count += _i_player_data->GetSpeed(_tag);

		_lerp_count = Clamp(_lerp_count, 0, 1);

		if (_lerp_count >= 1.f) 
		{
			_move_flag  = false;
			_lerp_count = 0;
			_i_player_data->SetPosition(_tag, _transform.position);
		}
	}
	else
	{
		float abs_x = fabsf(pad->GetPadStateX());
		float abs_z = fabsf(pad->GetPadStateY());
		
		int old_index_x = _index_num.x;
		int old_index_z = _index_num.z;

		if (abs_x > abs_z)
		{
			std::signbit(pad->GetPadStateX()) ? _index_num.x-- : _index_num.x++;
			_index_num.x = (int)Clamp(_index_num.x, 0, map_data[_index_num.z].size() - 1);
		}
		else if (abs_x < abs_z)
		{
			std::signbit(pad->GetPadStateY()) ? _index_num.z-- : _index_num.z++;

			_index_num.z = (int)Clamp(_index_num.z, 0, map_data.size() - 1);
		}

		if (map_data[_index_num.z][_index_num.x] != 'i' &&
			map_data[_index_num.z][_index_num.x] != 'w' &&
			map_data[_index_num.z][_index_num.x] != 'b')
		{
			_new_pos = Vector3_Right * _index_num.x + Vector3_Forward * -_index_num.z;
			_i_player_data->SetIndexNum(_tag, _index_num);
			_move_flag = true;
		}
		else
		{
			_index_num.x = old_index_x;
			_index_num.z = old_index_z;
		}

		_old_pos = _transform.position;
	}
}

void PlayerBase::IsMove(Controller* pad)
{
	/*auto&& map_data = _i_map_data->GetData();
	
	float abs_x = fabsf(pad->GetPadStateX());
	float abs_z = fabsf(pad->GetPadStateY());

	int old_index_x = _index_num.x;
	int old_index_z = _index_num.z;

	if (abs_x > abs_z)
	{
		std::signbit(pad->GetPadStateX()) ? _index_num.x-- : _index_num.x++;
		_index_num.x = (int)Clamp(_index_num.x, 0, map_data[_index_num.z].size() - 1);
		abs_z = 0;
	}
	else if (abs_x < abs_z)
	{
		std::signbit(pad->GetPadStateY()) ? _index_num.z-- : _index_num.z++;
		_index_num.z = (int)Clamp(_index_num.z, 0, map_data.size() - 1);
		abs_x = 0;
	}

	if (map_data[_index_num.z][_index_num.x] != 'i' &&
		map_data[_index_num.z][_index_num.x] != 'w' &&
		map_data[_index_num.z][_index_num.x] != 'b')
	{
		_new_pos = Vector3_Right * _index_num.x + Vector3_Forward * -_index_num.z;
		_i_player_data->SetIndexNum(_tag, _index_num);
	}
	else
	{
		_index_num.x = old_index_x;
		_index_num.z = old_index_z;
	}

	_old_pos = _transform.position;

	_transform.position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
	_lerp_count += (abs_x + abs_z) * _i_player_data->GetSpeed(_tag);

	_lerp_count = Clamp(_lerp_count, 0, 1);

	if (_lerp_count >= 1.f)
	{
		_lerp_count = 0;
		_i_player_data->SetPosition(_tag, _transform.position);
	}*/
}

//! 当たり判定の座標設定
void PlayerBase::SetCollisionPosition()
{
	auto collision_pos = _transform.position;
	collision_pos.y += _model->GetScale().y / 2;
	_hit_box->SetHitBoxPosition(collision_pos);
}

//! fn アームの生成
void PlayerBase::CreateArm()
{
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
