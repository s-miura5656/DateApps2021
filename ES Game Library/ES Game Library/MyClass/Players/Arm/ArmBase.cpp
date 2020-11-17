#include "ArmBase.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"

ArmBase::ArmBase()
{
	
}

ArmBase::~ArmBase()
{
}

int ArmBase::Update()
{
	MoveProtoType();

	return 0;
}

void ArmBase::Draw()
{
	auto collision_pos = arm_model->GetPosition();
	collision_pos.y = arm_model->GetScale().y / 2;
	_hit_box->SetHitBoxPosition(collision_pos);
	arm_model->Draw();
}

void ArmBase::SetPra(Vector3 pos, float angle) 
{
	arm_model->SetRotation(0, angle, 0);
	arm_model->SetPosition(pos);
}

void ArmBase::ArmShoot(int flag)
{
	arm_state = flag;
}

void ArmBase::Move()
{
	/*auto pad = ControllerManager::Instance().GetController(_player_tag);

	player_angle = MathHelper_Atan2(double(pad->GetPadStateX() - Axis_Center) / double(Axis_Max - Axis_Center),
		-double(pad->GetPadStateY() - Axis_Center) / double(Axis_Max - Axis_Center));

	arm_model->SetRotation(0, player_angle, 0);
	arm_model->Move(0, 0, arm_speed);*/
}

void ArmBase::MoveProtoType()
{
	arm_get_pos = arm_model->GetPosition();
	arm_get_rot = arm_model->GetRotation();

	auto player_get_pos = _iplayer_data->GetPosition(_player_tag);
	auto player_get_angle = _iplayer_data->GetAngle(_player_tag);

	auto pad = ControllerManager::Instance().GetController(_player_tag);

	dist = Vector3_Distance(player_get_pos, arm_get_pos);

	if (arm_state == RETURN_PUNCH)
	{
		Matrix  miss_rot;
		miss_rot = Matrix_CreateLookAt(arm_get_pos, player_get_pos, Vector3_Up);
		miss_rot = Matrix_Invert(miss_rot);
		arm_model->SetDirection(Quaternion_CreateFromRotationMatrix(miss_rot));

		arm_model->Move(0,0, arm_speed);
		if (dist <= 0.5) {
			arm_state = NO_PUNCH;
			dist = 0;
		}
	}
	else if (arm_state == PUNCH)
	{

		if (pad->GetPadStateX() != Axis_Center||
			pad->GetPadStateY() != Axis_Center)
		{
			player_angle = MathHelper_Atan2(double(pad->GetPadStateX() - Axis_Center) / double(Axis_Max - Axis_Center),
				-double(pad->GetPadStateY() - Axis_Center) / double(Axis_Max - Axis_Center));

			arm_model->SetRotation(0, player_angle, 0);
			arm_model->Move(0, 0, arm_speed);
		}

		for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
		{
			std::string name = PLAYER_TAG + std::to_string(i + 1);

			if (_player_tag == name)
				continue;

			if (_hit_box->IsHitObjects(name))
			{
				int damege = _iplayer_data->GetHitPoint(name) - _iplayer_data->GetAttackPowor(_player_tag);
				_iplayer_data->SetHitPoint(name, damege);
				arm_state = RETURN_PUNCH;
			}
		}
	}
	else if (arm_state == NO_PUNCH)
	{
		SetPra(player_get_pos, player_get_angle);
	}
}

