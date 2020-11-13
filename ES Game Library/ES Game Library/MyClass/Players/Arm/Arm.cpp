#include "Arm.h"


Arm::Arm(std::string name)
{
	_iplayer_data = new IPrayerData;
	_player_tag = name;

	int arm_num = GetTagNum(name);

	_tag = ARM_TAG + std::to_string(arm_num);

	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(_tag);
	_hit_box->SetHitBox(1, 1, 1);
}

Arm::~Arm()
{

}

bool Arm::Fileinitialize()
{
	return true;
}

bool Arm::Initialize()
{
	arm_model = GraphicsDevice.CreateModelFromFile(_T("Player/sword_01.X"));

	arm_state = NO_PUNCH;

	arm_speed = 0.1f;

	arm_model->SetScale(0.005f);

	hit_flag = false;

	return true;
}



