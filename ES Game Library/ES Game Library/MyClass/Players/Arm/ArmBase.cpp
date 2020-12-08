#include "ArmBase.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"
#include "../../Data/MyAlgorithm.h"

ArmBase::ArmBase()
{
	
}

ArmBase::~ArmBase()
{

}

int ArmBase::Update()
{
	auto pad = ControllerManager::Instance().GetController(_player_tag);

	_player_distance = Vector3_Distance(_i_player_data->GetPosition(_player_tag), _position);

	_arm_state = _i_arm_Data->GetState(_tag);

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
		if (_angle_point.size() >= _i_arm_Data->GetLimitRange(_tag))
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

		return 0;
	}

	//! アームの戻り状態の処理の判定
	if (_arm_state == ArmEnum::PunchState::RETURN_PUNCH)
	{
		ArmReturn();
		_shot_effect->Stop(effect_num);

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
		SpriteBatch.DrawString(_font, Vector2(0, 300), Color(0.f, 0.f, 0.f), _T("AnglePointSize:%d"), _angle_point.size());
		SpriteBatch.DrawString(_font, Vector2(0, 320), Color(0.f, 0.f, 0.f), _T("CreateCount:%d"), ArmBase::_create_count);
		SpriteBatch.DrawString(_font, Vector2(0, 340), Color(0.f, 0.f, 0.f), _T("Pos_X:%f"), _position.x);
		SpriteBatch.DrawString(_font, Vector2(0, 360), Color(0.f, 0.f, 0.f), _T("Pos_Z:%f"), _position.z);
	}
}

void ArmBase::Draw3D()
{
	//! モデルの座標指定と描画
	_model->SetPosition(_position);
	_model->SetRotation(0, _angle - 180, 0);
	_model->Draw();
	_model->SetRotation(0, _angle, 0);

	
	//! ヒットボックスの座標指定と描画
	auto box_pos = _position;
	box_pos.y += _hit_box->GetModelTag()->GetScale().y;
	auto a = DirectionFromAngle(Vector3(0, _angle, 0));
	_hit_box->SetHitBoxPosition(box_pos + a * 0.3f);
	_hit_box->Draw3D();

	//! エフェクトの座標指定と描画
	_shot_effect->SetSpeed(effect_num, 1.0f);
	_shot_effect->SetScale(effect_num, 1.0f);
	_shot_effect->SetRotation(effect_num, Vector3(0, _angle, 0));
	_shot_effect->SetPosition(effect_num, _position + (-a * 0.5f) + (Vector3_Up * 0.5f));
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
		_position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
		_lerp_count += _i_arm_Data->GetGoSpeed(_tag);

		if (_lerp_count >= 1.f)
		{
			_move_flag  = false;
			_angle_point.push_back(_position);
			_lerp_count = 0;

			//! パッドを倒していたらアームの向き入力状態
			if (pad->GetPadStateX() != Axis_Center || pad->GetPadStateY() != Axis_Center)
			{
				_angle = AngleCalculating(pad->GetPadStateX(), pad->GetPadStateY());
				_angle = AngleClamp(_angle);

				if (_angle != _old_angle)
				{
					_old_angle = _angle;
					_turn_flag = true;
				}
			}
		}
	}
	else
	{
		int old_index_x = _index_num.x;
		int old_index_z = _index_num.z;
		
		Vector3 dir = DirectionFromAngle(Vector3(0, _angle, 0));

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
			_new_pos = Vector3_Right * _index_num.x + Vector3_Forward * -_index_num.z;
			_move_flag = true;
		}
		else
		{
			_index_num.x = old_index_x;
			_index_num.z = old_index_z;
		}

		_old_pos = _position;
	}
}

bool ArmBase::TurnArm(Controller* pad)
{
	//! フラグがたっていたらアームの向き入力
	if (_turn_flag)
	{
		_wait_count++;

		if (_wait_count > 30)
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
	auto angle_point_size = _angle_point.size();

	Vector3 move_dir = Vector3_Normalize(_angle_point[angle_point_size - 1] - _position);

	auto dist = Vector3_Distance(_position, _angle_point[angle_point_size - 1]);

	//! 一定距離まで中継地点に近づいたら配列を削除
	if (dist < 0.3f && angle_point_size > 1)
	{
		_angle_point.erase(_angle_point.begin() + (angle_point_size - 1));
		return;
	}

	move_dir *= _i_arm_Data->GetReturnSpeed(_tag);

	_angle = -AngleCalculating(move_dir.x, move_dir.z);

	_position += move_dir;

	//! 移動が完了したら配列を削除
	if (move_dir == Vector3_Zero && angle_point_size > 1)
	{
		_angle_point.erase(_angle_point.begin() + (angle_point_size - 1));
	}
}

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
			}

			if (i_player_data->GetHitPoint(name) <= 0)
			{
				i_player_data->SetKillCount(_player_tag, i_player_data->GetKillCount(_player_tag) + 1);
				_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
				i_arm_data->SetState(_tag, _arm_state);
//				i_player_data->SetState(name, PlayerEnum::Animation::DEATH);
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
