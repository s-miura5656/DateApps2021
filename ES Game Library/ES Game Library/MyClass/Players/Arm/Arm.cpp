#include "Arm.h"

Arm::Arm()
{
}

Arm::~Arm()
{
}

bool Arm::Fileinitialize()
{
	arm_model = GraphicsDevice.CreateModelFromFile(_T("Player/sword_01.X"));

	return 0;
}

bool Arm::Initialize()
{
	arm_state = NO_PUNCH;

	arm_speed = 0.1f;

	arm_model->SetScale(0.005f);

	return 0;
}

int Arm::Update(Vector3 player_pos, float player_angle)
{
	arm_get_pos = arm_model->GetPosition();
	arm_get_rot = arm_model->GetRotation();

	player_get_pos = player_pos;
	player_get_angle = player_angle;

	dist = Vector3_Distance(player_get_pos, arm_get_pos);


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
		SetPra(player_get_pos, player_get_angle);
	}


	return true;
}

void Arm::ArmShoot(int flag)
{
	arm_state = flag;
}

void Arm::SetPra(Vector3 pos, float angle) {
	arm_model->SetRotation(0, angle,0);
	arm_model->SetPosition(pos);
}