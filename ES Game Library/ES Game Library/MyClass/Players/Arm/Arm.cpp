#include "Arm.h"

Arm::Arm(std::string name)
{
	_iplayer_data = new IPrayerData;
	player_name = name;
}

Arm::~Arm()
{

}

bool Arm::Fileinitialize()
{
	return 0;
}

bool Arm::Initialize()
{

	arm_model = GraphicsDevice.CreateModelFromFile(_T("Player/sword_01.X"));

	arm_state = NO_PUNCH;

	arm_speed = 0.1f;

	arm_model->SetScale(0.005f);



	return 0;
}



