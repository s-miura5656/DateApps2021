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
	
	_dist = Vector3_Distance(_iplayer_data->GetPosition(_player_tag), _model->GetPosition());

	//! アームの発射状態の判定
	if (pad->GetButtonState(GamePad_Button2) && arm_state == ArmEnum::PunchState::PUNCH)
	{
		_punch_type = ArmEnum::PunchType::PUSH;
	}
	else if (pad->GetButtonState(GamePad_Button3) && arm_state == ArmEnum::PunchState::PUNCH)
	{
		_punch_type = ArmEnum::PunchType::PULL;
	}
	else
	{
		arm_state = ArmEnum::PunchState::RETURN_PUNCH;
		_iarm_Data->SetState(_tag, arm_state);
	}

	if (arm_state == ArmEnum::PunchState::PUNCH)
	{
		ArmFire(pad);

		if (_angle_point.size() >= _iarm_Data->GetLimitRange(_tag))
			arm_state = ArmEnum::PunchState::RETURN_PUNCH;

	}

	//! アームの戻り状態の処理の判定
	if (arm_state == ArmEnum::PunchState::RETURN_PUNCH)
	{
		ArmReturn();

		if (_dist < 0.6f)
		{
			arm_state = ArmEnum::PunchState::NO_PUNCH;
			_iarm_Data->SetState(_tag, arm_state);
		}
	}
	
	//! アームが戻ってきた時の処理の判定
	if (arm_state == ArmEnum::PunchState::NO_PUNCH)
	{
		_iplayer_data->SetState(_player_tag, PlayerEnum::Animation:: WAIT);
	}

	

	return 0;
}

void ArmBase::Draw2D()
{
	if (_tag == "Arm_1")
	{
		SpriteBatch.DrawString(_font, Vector2(0, 300), Color(1.f, 0.f, 0.f), _T("Speed:%f"), _iarm_Data->GetSpeed(_tag));
		SpriteBatch.DrawString(_font, Vector2(0, 350), Color(1.f, 0.f, 0.f), _T("AnglePointSize:%d"), _angle_point.size());
		SpriteBatch.DrawString(_font, Vector2(0, 400), Color(1.f, 0.f, 0.f), _T("LimitRange:%d"), _iarm_Data->GetLimitRange(_tag));
		SpriteBatch.DrawString(_font, Vector2(0, 450), Color(1.f, 0.f, 0.f), _T("Dist:%f"), _dist);
	}
}

void ArmBase::Draw3D()
{
	_model->SetRotation(0, _angle - 180, 0);
	_model->Draw();
	_model->SetRotation(0, _angle, 0);

	auto box_pos = _model->GetPosition();
	_hit_box->SetHitBoxPosition(box_pos);
	_hit_box->Draw3D();
}

//! @fn アームの移動
//! @brief アームの移動を処理する
//! @param コントローラー
void ArmBase::Move(Controller* pad)
{
	auto&& map_data = _imap_data->GetData();

	if (_move_flag)
	{
		_position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
		_lerp_count += _iarm_Data->GetSpeed(_tag);

		if (_lerp_count >= 1.f)
		{
			_move_flag = false;
			_lerp_count = 0;
			_iplayer_data->SetState(_tag, PlayerEnum::Animation::WAIT);
		}
	}
	else
	{
		float abs_x = fabsf(pad->GetPadStateX());
		float abs_z = fabsf(pad->GetPadStateY());

		if (abs_x > 30 && abs_x > abs_z)
		{
			int old_index = _index_num.x;
			std::signbit(pad->GetPadStateX()) ? _index_num.x-- : _index_num.x++;
			_index_num.x = Clamp(_index_num.x, 1, map_data[_index_num.z].size() - 3);

			if (map_data[_index_num.z][_index_num.x] != 'i' && map_data[_index_num.z][_index_num.x] != 'w')
			{
				_new_pos = Vector3(1 * _index_num.x, 0.5f, 1 * -_index_num.z);
				_angle_point.push_back(_new_pos);
				_move_flag = true;
			}
			else
			{
				_index_num.x = old_index;
				arm_state = ArmEnum::PunchState::RETURN_PUNCH;
				_iarm_Data->SetState(_tag, arm_state);
			}
		}

		if (abs_z > 30 && abs_x < abs_z)
		{
			int old_index = _index_num.z;
			std::signbit(pad->GetPadStateY()) ? _index_num.z-- : _index_num.z++;
			_index_num.z = Clamp(_index_num.z, 1, map_data.size() - 2);

			if (map_data[_index_num.z][_index_num.x] != 'i' && map_data[_index_num.z][_index_num.x] != 'w')
			{
				_new_pos = Vector3(1 * _index_num.x, 0.5f, 1 * -_index_num.z);
				_angle_point.push_back(_new_pos);
				_move_flag = true;
			}
			else
			{
				_index_num.z = old_index;
				arm_state = ArmEnum::PunchState::RETURN_PUNCH;
				_iarm_Data->SetState(_tag, arm_state);
			}
		}

		_old_pos = _position;
	}
	_model->SetPosition(_position);
}

//! @fn アームの戻り
//! @brief アームの戻り移動を処理する
void ArmBase::ArmReturn()
{
	auto a = _angle_point.size();

	Vector3 move_dir = Vector3_Normalize(_angle_point[a - 1] - _model->GetPosition());

	auto dist = Vector3_Distance(_model->GetPosition(), _angle_point[a - 1]);

	if (dist < 0.1f && a > 1)
	{
		_angle_point.erase(_angle_point.begin() + (a - 1));
		return;
	}

	move_dir *= _iarm_Data->GetSpeed(_tag);

	_angle = -AngleCalculating(move_dir.x, move_dir.z);

	_model->SetRotation(0, _angle, 0);

	_position = _model->GetPosition() + move_dir;

	if (move_dir == Vector3_Zero && a > 1)
	{
		_angle_point.erase(_angle_point.begin() + (a - 1));
	}

	auto map_data = _imap_data->GetData();

	_model->SetPosition(_position);
}

void ArmBase::ArmFire(Controller* pad)
{
	if (_punch_type == ArmEnum::PunchType::PUSH)
	{
		Move(pad);

		Push();
	}
	else if (_punch_type == ArmEnum::PunchType::PULL)
	{
		Move(pad);

		Pull();
	}
}

//! @fn 他のプレイヤーを押す
//! @brief 他のプレイヤーを押す
void ArmBase::Push()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		if (name == _player_tag)
			continue;

		if (_hit_box->IsHitObjects(name))
		{
			arm_state = ArmEnum::PunchState::RETURN_PUNCH;
			_iarm_Data->SetState(_tag, arm_state);
			_iplayer_data->SetState(name, PlayerEnum::Animation::DAMAGE);

			IndexNum index = _iplayer_data->GetIndexNum(name);

			if (_angle == 0)
			{
				index.z -= 1;
			}
			else if (_angle == 90)
			{
				index.x += 1;
			}
			else if (_angle == 180)
			{
				index.z += 1;
			}
			else if (_angle == 270)
			{
				index.x -= 1;
			}

			_iplayer_data->SetIndexNum(name, index);
			break;
		}
	}

	
}

//! @fn 他のプレイヤーを引っ張る
//! @brief 他のプレイヤーを引っ張る
void ArmBase::Pull()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		if (name == _player_tag)
			continue;

		if (_hit_box->IsHitObjects(name))
		{
			arm_state = ArmEnum::PunchState::RETURN_PUNCH;
			_iplayer_data->SetState(name, PlayerEnum::Animation::DAMAGE);

			IndexNum index = _iplayer_data->GetIndexNum(name);

			if (_angle == 0)
			{
				index.z += 1;
			}
			else if (_angle == 90)
			{
				index.x -= 1;
			}
			else if (_angle == 180)
			{
				index.z -= 1;
			}
			else if (_angle == 270)
			{
				index.x += 1;
			}

			_iplayer_data->SetIndexNum(name, index);

			break;
		}
	}
}


