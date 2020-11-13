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
	
	arm_get_pos = arm_model->GetPosition();
	arm_get_rot = arm_model->GetRotation();

	auto player_pos = _iplayer_data->GetPosition(_player_tag);
	player_angle = _iplayer_data->GetAngle(_player_tag);

	dist = Vector3_Distance(player_pos, arm_get_pos);

	if (arm_state == PUNCH) {
		Move(arm_speed);
	}
	else {
		SetPra(player_pos, player_angle);
	}

	for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		if (_player_tag == name)
			continue;

		if (_hit_box->IsHitObjects(name))
		{
			//exit(0);
		}
	}
	

	if (hit_flag) {
		Move(-arm_speed);
		if (dist <= 0.5) {
			dist = 0;
			hit_flag = false;
			arm_state = NO_PUNCH;
		}
	}

	/*if (arm_state == RETURN_PUNCH)
	{
		arm_model->Move(0, 0, -arm_speed);
		if (dist <= 0.5) {
			arm_state = NO_PUNCH;
			dist = 0;
		}
	}
	else if (arm_state == PUNCH)
	{
		arm_model->Move(0, 0, arm_speed);
		if (dist >= 5)
		{
			dist = 5;
			arm_state = RETURN_PUNCH;
		}
	}
	else if (arm_state == NO_PUNCH)
	{
		SetPra(player_pos, player_angle);
	}*/

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

void ArmBase::Move(float speed)
{
	auto pad = ControllerManager::Instance().GetController(_tag);

	player_angle = MathHelper_Atan2(double(pad->GetPadStateX() - Axis_Center) / double(Axis_Max - Axis_Center),
		-double(pad->GetPadStateY() - Axis_Center) / double(Axis_Max - Axis_Center));

	arm_model->SetRotation(0, player_angle, 0);
	arm_model->Move(0, 0, speed);
}

