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
		if (pad->GetPadStateX() != Axis_Center || pad->GetPadStateY() != Axis_Center)
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
	/*if (_tag == "Arm_1")
	{
		SpriteBatch.DrawString(_font, Vector2(0, 300), Color(1.f, 1.f, 1.f), _T("ANGLE:%f"), _angle);
		SpriteBatch.DrawString(_font, Vector2(0, 350), Color(1.f, 1.f, 1.f), _T("POS_X:%f"), _model->GetPosition().x);
		SpriteBatch.DrawString(_font, Vector2(0, 400), Color(1.f, 1.f, 1.f), _T("POS_Z:%f"), _model->GetPosition().z);
	}*/
}

void ArmBase::Draw3D()
{
	_model->Draw();
	_hit_box->Draw3D();
}

void ArmBase::Move(Controller* pad)
{
	_angle = AngleCalculating(pad->GetPadStateX(), pad->GetPadStateY());
	_angle = AngleClamp(_angle);

	if ((int)_angle != (int)_old_angle)
	{
		_angle_point.push_back(_position);
	}

	_model->SetRotation(0, _angle, 0);

	_old_angle = (int)_angle;

#pragma region ˆÚ“®‚Æ“–‚½‚è”»’è
	auto hit_list = _hit_box->IsHitBoxList(_player_tag);

	Vector3 move_dir = Vector3_Zero;

	auto map_pos = _imap_data->GetPosition();

	if (!hit_list.empty())
	{
		auto model = _hit_box->IshitNearestObject(hit_list, _position, _model->GetFrontVector());

		auto hit_box = _hit_box->GetModelTag();

		if (hit_box->GetPosition().x + hit_box->GetScale().x / 2 > model->GetPosition().x - model->GetScale().x / 2 ||
			hit_box->GetPosition().x - hit_box->GetScale().x / 2 < model->GetPosition().x + model->GetScale().x / 2 ||
			hit_box->GetPosition().z + hit_box->GetScale().z / 2 < model->GetPosition().z - model->GetScale().z / 2 ||
			hit_box->GetPosition().z - hit_box->GetScale().z / 2 < model->GetPosition().z + model->GetScale().z / 2)
		{
			_position = _old_pos;
		}

		_model->SetPosition(_position);

		move_dir = SlidingOnWallVectorCreate(model, _model->GetPosition(), _model->GetFrontVector());

		_position += move_dir * 0.1f;
	}
	else
	{
		move_dir = MoveDirection(pad->GetPadStateX(), pad->GetPadStateY());
		move_dir *= 0.1f;
		_position = _model->GetPosition() + move_dir;
	}
#pragma endregion

	_position.x = Clamp(_position.x, 1, map_pos[12].x);
	_position.z = Clamp(_position.z, map_pos[142].z, -1);

	_model->SetPosition(_position);

	_old_pos = _position;
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

	move_dir *= 0.1f;

	_angle = -AngleCalculating(move_dir.x, move_dir.z);

	_model->SetRotation(0, _angle, 0);

	_position = _model->GetPosition() + move_dir;

	if (move_dir == Vector3_Zero && a > 1)
	{
		_angle_point.erase(_angle_point.begin() + (a - 1));
	}

	auto map_pos = _imap_data->GetPosition();

	_position.x = Clamp(_position.x, 1, map_pos[12].x);
	_position.z = Clamp(_position.z, map_pos[142].z, -1);

	_model->SetPosition(_position);
}

float ArmBase::AngleClamp(float angle)
{
	if (angle >= 0 - 45 && angle < 0 + 45)
	{
		angle = 0;
	}
	else if (angle >= 90 - 45 && angle < 90 + 45)
	{
		angle = 90;

	}
	else if (angle >= 180 - 45 && angle < 180 + 45)
	{
		angle = 180;
	}
	else if (angle >= 270 - 45 && angle < 270 + 45)
	{
		angle = 270;
	}

	return angle;
}






