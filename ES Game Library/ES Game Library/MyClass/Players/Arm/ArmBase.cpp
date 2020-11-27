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

	if (pad->GetButtonState(GamePad_Button1) && arm_state == ArmEnum::PunchState::PUNCH)
	{
		arm_state = ArmEnum::PunchState::PUNCH;
	}
	else
	{
		arm_state = ArmEnum::PunchState::RETURN_PUNCH;
	}

	if (arm_state == ArmEnum::PunchState::PUNCH)
	{
		Move(pad);

		if (_angle_point.size() > 10)
			arm_state = ArmEnum::PunchState::RETURN_PUNCH;
	}
	
	if (arm_state == ArmEnum::PunchState::RETURN_PUNCH)
	{
		ReturnArm();

		if (_dist < 0.3f)
			arm_state = ArmEnum::PunchState::NO_PUNCH;
	}
	
	if (arm_state == ArmEnum::PunchState::NO_PUNCH)
	{
		_iplayer_data->SetState(_player_tag, PlayerEnum::WAIT);
	}

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		if (name == _player_tag)
			continue;

		if (_hit_box->IsHitObjects(name))
		{
			auto damage = _iplayer_data->GetHitPoint(name) - _iarm_Data->GetAttackPowor(_tag);
			_iplayer_data->SetHitPoint(name, damage);
			arm_state = ArmEnum::PunchState::RETURN_PUNCH;
			break;
		}
	}

	auto box_pos = _model->GetPosition() + Vector3_Up * 0.5f;

	_hit_box->SetHitBoxPosition(box_pos);

	return 0;
}

void ArmBase::Draw2D()
{
	if (_tag == "Arm_1")
	{
		//SpriteBatch.DrawString(_font, Vector2(0, 300), Color(1.f, 1.f, 1.f), _T("ANGLE:%d"), );
		SpriteBatch.DrawString(_font, Vector2(0, 350), Color(1.f, 1.f, 1.f), _T("POS_X:%f"), _model->GetPosition().x);
		SpriteBatch.DrawString(_font, Vector2(0, 400), Color(1.f, 1.f, 1.f), _T("POS_Z:%f"), _model->GetPosition().z);
	}
}

void ArmBase::Draw3D()
{
	_model->SetRotation(90, _angle, 180);
	_model->Draw();
	_model->SetRotation(0, _angle, 0);
	_hit_box->Draw3D();
}

void ArmBase::Move(Controller* pad)
{
	auto&& map_data = _imap_data->GetData();

	if (_move_flag)
	{
		_position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
		_lerp_count += 0.05f;

		if (_lerp_count >= 1.f)
		{
			_move_flag = false;
			_lerp_count = 0;
			_iplayer_data->SetState(_tag, PlayerEnum::WAIT);
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
				_new_pos = Vector3(1 * _index_num.x, 1, 1 * -_index_num.z);
				_angle_point.push_back(_new_pos);
				_move_flag = true;
			}
			else
			{
				_index_num.x = old_index;
			}
		}

		if (abs_z > 30 && abs_x < abs_z)
		{
			int old_index = _index_num.z;
			std::signbit(pad->GetPadStateY()) ? _index_num.z-- : _index_num.z++;
			_index_num.z = Clamp(_index_num.z, 1, map_data.size() - 2);

			if (map_data[_index_num.z][_index_num.x] != 'i' && map_data[_index_num.z][_index_num.x] != 'w')
			{
				_new_pos = Vector3(1 * _index_num.x, 1, 1 * -_index_num.z);
				_angle_point.push_back(_new_pos);
				_move_flag = true;
			}
			else
			{
				_index_num.z = old_index;
			}
		}

		_old_pos = _position;
	}
	_model->SetPosition(_position);
}

void ArmBase::ReturnArm()
{
	auto a = _angle_point.size();

	Vector3 move_dir = Vector3_Normalize(_angle_point[a - 1] - _model->GetPosition());

	auto dist = Vector3_Distance(_model->GetPosition(), _angle_point[a - 1]);

	if (dist < 0.1f && a > 1)
	{
		_angle_point.erase(_angle_point.begin() + (a - 1));
		return;
	}

	move_dir *= 0.2f;

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
