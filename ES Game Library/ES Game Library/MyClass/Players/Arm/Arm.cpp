#include "Arm.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Managers/ResouceManager/ResouceManager.h"

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

bool Arm::Initialize()
{
	//! File
	_font = GraphicsDevice.CreateSpriteFont(_T("SketchFlow Print"), 50);
	_model = ResouceManager::Instance().LoadModelFile(_T("Player/robot_hand01.X"));

	//! Position
	_position = _iplayer_data->GetPosition(_player_tag) + Vector3(0, 0.5f, 0);
	_old_pos = _position + Vector3(0, 0.5f, 0);
	_new_pos = _position + Vector3(0, 0.5f, 0);
	_model->SetPosition(_new_pos);
	_index_num = _iplayer_data->GetIndexNum(_player_tag);
	_angle_point.push_back(_position);

	//! Angle
	_angle = _iplayer_data->GetAngle(_player_tag);
	_model->SetRotation(0, _iplayer_data->GetAngle(_player_tag), 0);
	_old_angle = _angle;

	//! State
	arm_state = ArmEnum::PunchState::PUNCH;
	_iarm_Data->SetState(_tag, arm_state);
	hit_flag = false;

	//! Speed
	arm_speed = 0.07f;

	//! Scale
	_model->SetScale(2.f);

	//! Material
	Material mat;
	mat.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	mat.Ambient  = Color(1.0f, 1.0f, 1.0f);
	mat.Specular = Color(1.0f, 1.0f, 1.0f);

	_model->SetMaterial(mat);

	return true;
}



