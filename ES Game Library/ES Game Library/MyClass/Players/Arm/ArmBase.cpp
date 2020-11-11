#include "ArmBase.h"

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

	auto player_pos = _iplayer_data->GetPosition(player_name);
	auto player_angle = _iplayer_data->GetAngle(player_name);

	dist = Vector3_Distance(player_pos, arm_get_pos);


	if (arm_state == RETURN_PUNCH)
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
	}

	return 0;
}

void ArmBase::Draw()
{
	arm_model->Draw();
}

void ArmBase::SetPra(Vector3 pos, float angle) {
	arm_model->SetRotation(0, angle, 0);
	arm_model->SetPosition(pos);
}

void ArmBase::ArmShoot(int flag)
{
	arm_state = flag;
}
