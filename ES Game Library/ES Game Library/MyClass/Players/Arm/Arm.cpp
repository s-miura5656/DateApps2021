#include "Arm.h"
#include "../../Data/MyAlgorithm.h"

Arm::Arm(std::string name)
{
	_player_tag = name;

	int arm_num = GetTagNum(name);

	_tag = ARM_TAG + std::to_string(arm_num);

	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(0.5f);

	_iplayer_data = new IPrayerData;
	_iarm_Data = new IArmData;
}

Arm::~Arm()
{
	delete _iarm_Data;
	delete _iplayer_data;
}

bool Arm::Fileinitialize()
{
	return true;
}

bool Arm::Initialize()
{
	_font = GraphicsDevice.CreateSpriteFont(_T("SketchFlow Print"), 50);
	_model = GraphicsDevice.CreateModelFromFile(_T("Player/robo_arm.X"));

	_model->SetRotation(0, _iplayer_data->GetAngle(_player_tag), 0);
	_position = _iplayer_data->GetPosition(_player_tag);
	_old_pos = _position + Vector3(0, 0.5f, 0);
	_new_pos = _position + Vector3(0, 0.5f, 0);

	_index_num = _iplayer_data->GetIndexNum();

	_model->SetPosition(_new_pos);
	_angle_point.push_back(_position);

	_angle = _iplayer_data->GetAngle(_player_tag);
	_model->SetRotation(0, _angle, 0);
	_old_angle = _angle;
	arm_state = ArmEnum::PunchState::PUNCH;

	arm_speed = 0.07f;

	_model->SetScale(2.f);

	hit_flag = false;

	return true;
}



