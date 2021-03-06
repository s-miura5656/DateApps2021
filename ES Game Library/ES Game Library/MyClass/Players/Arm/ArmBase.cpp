#include "ArmBase.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Managers/SceneManager/SceneManager.h"
#include "../../ParticleSystem/Particle.h"

ArmBase::ArmBase()
{
	
}

ArmBase::~ArmBase()
{

}

int ArmBase::Update()
{
	auto pad = ControllerManager::Instance().GetController(_player_tag);

	_player_distance = Vector3_Distance(_i_player_data->GetPosition(_player_tag), _transform.position);

	_arm_state = _i_arm_Data->GetState(_tag);

	_i_arm_Data->SetAnglePositions(_tag, _angle_positions);
	_i_arm_Data->SetAngles(_tag, _angles);

	if (_scale < 2) 
	{
		_scale += 2.0f / 10.0f;
	}

	//! アームの発射状態の判定
	if (pad->GetButtonState(GamePad_Button2) && _arm_state == ArmEnum::PunchState::PUNCH)
	{
		_arm_state = ArmEnum::PunchState::PUNCH;
		_i_arm_Data->SetState(_tag, _arm_state);
	}
	else
	{
		_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
		_i_arm_Data->SetState(_tag, _arm_state);
	}

	//! アームを発射している状態の処理
	if (_arm_state == ArmEnum::PunchState::PUNCH)
	{
		//! アームの最大距離の判定
		if (_angle_positions.size() >= _i_arm_Data->GetLimitRange(_tag))
		{
			_wait_count++;

			if (_wait_count >= 30)
			{
				_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
				_i_arm_Data->SetState(_tag, _arm_state);
				_wait_count = 0;
			}
		}
		else
		{
			MoveArm(pad);
		}

		//! 当たり判定
		HitOtherObject();

		SetCollisionPosition();

		_shot_effect->SetPosition(_transform.position);

		return 0;
	}

	//! アームの戻り状態の処理の判定
	if (_arm_state == ArmEnum::PunchState::RETURN_PUNCH)
	{
		ArmReturn();
		_shot_effect->Stop();

		if (_player_distance < 0.6f)
		{
			_arm_state = ArmEnum::PunchState::NO_PUNCH;
			_i_arm_Data->SetState(_tag, _arm_state);
		}
	}
	
	//! アームが戻ってきた時の処理の判定
	if (_arm_state == ArmEnum::PunchState::NO_PUNCH)
	{
		_i_player_data->SetState(_player_tag, PlayerEnum::Animation::WAIT);
	}

	return 0;
}

void ArmBase::Draw2D()
{
	if (_tag == "Arm_1")
	{
//		SpriteBatch.DrawString(_font, Vector2(0, 300), Color(0.f, 0.f, 0.f), _T("AnglePointSize:%d"), _angle_positions.size());
//		SpriteBatch.DrawString(_font, Vector2(0, 320), Color(0.f, 0.f, 0.f), _T("CreateCount:%d"), ArmBase::_create_count);
//		SpriteBatch.DrawString(_font, Vector2(0, 340), Color(0.f, 0.f, 0.f), _T("Pos_X:%f"), _position.x);
//		SpriteBatch.DrawString(_font, Vector2(0, 360), Color(0.f, 0.f, 0.f), _T("Pos_Z:%f"), _position.z);
	}
//	auto scale = _hit_box->GetModelTag()->GetScale();
//	SpriteBatch.DrawString(_font, Vector2(0, 380), Color(255.f, 0.f, 0.f), _T("Scale:%0.1f, %0.1f, %0.1f"), scale.x, scale.y, scale.z);
}

void ArmBase::Draw3D()
{
	//! モデルの座標を
	_model->SetPosition(_transform.position);
	_model->SetScale(_scale);
	_model->SetRotation(0, _transform.rotation.y - 180, 0);
	_model->SetMaterial(_model_material);

	//! シェーダーにパラメーターを送る
	auto camera = SceneCamera::Instance().GetCamera();

	Matrix world = _model->GetWorldMatrix();
	_shader->SetParameter("wvp", world * camera->GetViewProjectionMatrix());
	_shader->SetParameter("eye_pos", camera.GetPosition());
	_shader->SetParameter("model_ambient", _model_material.Ambient);
	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetTechnique("FixModel_S1");

	_model->Draw(_shader);
	_model->SetRotation(0, _transform.rotation.y, 0);

	//! ヒットボックスの座標指定と描画
	_hit_box->SetModelPosition();
	_hit_box->SetModelScale();
	_hit_box->Draw3D();

	//! エフェクトの座標指定と描画
	_shot_effect->SetDrawRotationY(_transform.rotation.y, DirectionFromAngle(Vector3(0, _transform.rotation.y, 0)));
	_shot_effect->Draw();
}

//! @fn アームの移動(曲がる)
//! @brief アームの移動を処理する
//! @param コントローラー
void ArmBase::MoveArm(Controller* pad)
{
	auto&& map_data = _i_map_data->GetData();

	if (TurnArm(pad))
		return;

	//! 移動中かそうでないか判定
	if (_move_flag)
	{
		_transform.position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
		_lerp_count += _i_arm_Data->GetGoSpeed(_tag);
		_shot_effect->PlayOneShot();

		if (_lerp_count >= 1.f)
		{
			_move_flag  = false;
			_lerp_count = 0;
			_angle_positions.push_back(_transform.position);

			ChangeDirection(pad);

			_angles.push_back(_transform.rotation.y);
		}
	}
	else
	{
		int old_index_x = _index_num.x;
		int old_index_z = _index_num.z;
		
		Vector3 dir = DirectionFromAngle(Vector3(0, _transform.rotation.y, 0));

		auto abs_x = fabs(dir.x);
		auto abs_z = fabs(dir.z);
		
		//! 方向の絶対値を判定してから、大きいほうの軸の符号から進む方向を決定
		if (abs_x > abs_z)
		{
			signbit(dir.x) ? _index_num.x-- : _index_num.x++;
			_index_num.x = Clamp(_index_num.x, 0, map_data[_index_num.z].size() - 1);
		}
		else if (abs_x < abs_z)
		{
			signbit(dir.z) ? _index_num.z++ : _index_num.z--;
			_index_num.z = Clamp(_index_num.z, 0, map_data.size() - 1);
		}
		
		//! 壁の判定
		if (map_data[_index_num.z][_index_num.x] != 'i' &&
			map_data[_index_num.z][_index_num.x] != 'w')
		{
			_new_pos = Vector3_Right * _index_num.x + Vector3_Forward * -_index_num.z + Vector3(0, 0.5f, 0);
			_move_flag = true;
		}
		else if (map_data[_index_num.z][_index_num.x] == 'i' ||
				 map_data[_index_num.z][_index_num.x] == 'w')
		{
			_index_num.x = old_index_x;
			_index_num.z = old_index_z;
			_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
			_i_arm_Data->SetState(_tag, _arm_state);
			_wall_hit_effect->SetPosition(_transform.position);
			_wall_hit_effect->PlayOneShot();
		}
		else
		{
			_index_num.x = old_index_x;
			_index_num.z = old_index_z;
		}

		_old_pos = _transform.position;
	}
}

bool ArmBase::TurnArm(Controller* pad)
{
	//! フラグがたっていたらアームの向き入力
	if (_turn_flag)
	{
		_wait_count++;

		if (_wait_count > 15)
		{
			_wait_count = 0;
			_turn_flag = false;
		}
	}

	return _turn_flag;
}

//! @fn アームの戻り
//! @brief アームの戻り移動を処理する
void ArmBase::ArmReturn()
{
	auto angle_point_size = _angle_positions.size();

	Vector3 move_dir = Vector3_Normalize(_angle_positions[angle_point_size - 1] - _transform.position);

	auto dist = Vector3_Distance(_transform.position, _angle_positions[angle_point_size - 1]);

	//! 一定距離まで中継地点に近づいたら配列を削除
	if (dist < 0.3f && angle_point_size > 1)
	{
		_angle_positions.erase(_angle_positions.begin() + (angle_point_size - 1));
		return;
	}

	move_dir *= _i_arm_Data->GetReturnSpeed(_tag);

	_transform.rotation.y = -AngleCalculating(move_dir.x, move_dir.z);

	_transform.position += move_dir;

	//! 移動が完了したら配列を削除
	if (move_dir == Vector3_Zero && angle_point_size > 1)
	{
		_angle_positions.erase(_angle_positions.begin() + (angle_point_size - 1));
	}
}

//! @fn アームの当たり判定
//! @brief アームが他の当たり判定と当たった時に判定する
void ArmBase::HitOtherObject()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		//! 自分のタグだったら次へ
		if (name == _player_tag)
			continue;

		//! プレイヤーに当たったら
		if (_hit_box->IsHitObjectsSquare(name))
		{
			auto&& i_player_data = _i_player_data.get();
			auto&& i_arm_data    = _i_arm_Data.get();
			
			int damege = i_player_data->GetAttackPowor(_player_tag);
			int hitpoint = i_player_data->GetHitPoint(name);
			
			hitpoint -= damege;

			//! ダメージ硬直ではないときにHPを減らす
			if (i_player_data->GetState(name) != PlayerEnum::Animation::DAMAGE)
			{
				i_player_data->SetHitPoint(name, hitpoint);
				auto screen_pos = GraphicsDevice.WorldToScreen(_transform.position);
				screen_pos.z = SpriteBatch_TopMost;
				i_arm_data->SetHitPosition(_tag, screen_pos);
			}

			if (i_player_data->GetState(name) == PlayerEnum::Animation::DEATH)
				break;

			if (i_player_data->GetHitPoint(name) <= 0)
			{
				i_player_data->SetKillCount(_player_tag, i_player_data->GetKillCount(_player_tag) + 1);
				i_player_data->SetRankingPoint(_player_tag, i_player_data->GetRankingPoint(_player_tag) + 100);
				_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
				i_arm_data->SetState(_tag, _arm_state);
				i_player_data->SetState(name, PlayerEnum::Animation::DAMAGE);
			}
			else
			{
				_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
				i_arm_data->SetState(_tag, _arm_state);
				i_player_data->SetState(name, PlayerEnum::Animation::DAMAGE);
			}
			
			break;
		}
	}
}

//! @fn 当たり判定の座標設定
//! @brief 当たり判定の座標を設定する
void ArmBase::SetCollisionPosition()
{
	auto box_pos = _transform.position;
	auto dir = DirectionFromAngle(Vector3(0, _transform.rotation.y, 0));
	_hit_box->SetHitBoxPosition(box_pos + dir * 0.4f);
}

//! @fn アームの向きを変更
//! @brief パッドの向きからアームの向きを変更
void ArmBase::ChangeDirection(Controller* pad)
{
	//! パッドを倒していたらアームの向き入力状態
	if (pad->GetPadStateX() != Axis_Center || pad->GetPadStateY() != Axis_Center)
	{
		float angle = AngleCalculating(pad->GetPadStateX(), pad->GetPadStateY());
		angle = AngleClamp(angle);

		auto&& map_data = _i_map_data->GetData();

		int old_index_x = _index_num.x;
		int old_index_z = _index_num.z;

		Vector3 dir = DirectionFromAngle(Vector3(0, angle, 0));

		auto abs_x = fabs(dir.x);
		auto abs_z = fabs(dir.z);

		//! 方向の絶対値を判定してから、大きいほうの軸の符号から進む方向を決定
		if (abs_x > abs_z)
		{
			signbit(dir.x) ? old_index_x-- : old_index_x++;
			old_index_x = Clamp(old_index_x, 0, map_data[old_index_z].size() - 1);
		}
		else if (abs_x < abs_z)
		{
			signbit(dir.z) ? old_index_z++ : old_index_z--;
			old_index_z = Clamp(old_index_z, 0, map_data.size() - 1);
		}

		//! 壁の判定
		if (map_data[old_index_z][old_index_x] != 'i' &&
			map_data[old_index_z][old_index_x] != 'w')
		{
			//! 向きが変わっていたら向きを更新
			if (angle != _old_angle)
			{
				_shot_effect->Stop();
				_old_angle = angle;
				_turn_flag = true;
			}

			_transform.rotation.y = angle;
		}
	}
}

