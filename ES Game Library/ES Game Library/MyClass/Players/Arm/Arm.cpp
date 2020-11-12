#include "Arm.h"

Arm::Arm(std::string name, std::string arm_name)
{
	_iplayer_data = new IPrayerData;
	_player_name = name;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(arm_name);
	_hit_box->SetHitBox(1, 1, 1);
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

	hit_flag = false;

	return 0;
}



