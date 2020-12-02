#include "Arm.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Managers/ResouceManager/ResouceManager.h"

int Arm::_create_count = 0;

Arm::Arm(std::string name)
{
	_player_tag = name;

	int arm_num = GetTagNum(name);

	_tag = ARM_TAG + std::to_string(arm_num);

	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(0.8f);

	_i_player_data = new IPrayerData;
	_i_arm_Data	   = new IArmData;
	_i_map_data    = new IMapData;

	_create_count++;
}

Arm::~Arm()
{
	delete _i_map_data;
	delete _i_arm_Data;
	delete _i_player_data;
	_hit_box.reset();

	_create_count--;
}

bool Arm::Initialize()
{
	//! File
	_font  = ResouceManager::Instance().LordFontFile(_T("SketchFlow Print"), 20);
	_model = ResouceManager::Instance().LoadModelFile(_T("Player/robot_hand01.X"));
	
	//! Angle
	_angle = _i_player_data->GetAngle(_player_tag);
	_old_angle = _angle;

	//! Position
	_position = _i_player_data->GetPosition(_player_tag);
	_angle_point.push_back(_position);
	_old_pos = _position;
	_new_pos = _position;
	_index_num = _i_player_data->GetIndexNum(_player_tag);

	//! State
	_arm_state = ArmEnum::PunchState::PUNCH;
	_i_arm_Data->SetState(_tag, _arm_state);

	//! Scale
	_model->SetScale(2.f);

	//! distance
	_player_distance = FLT_MAX;

	//! Material
	Material mat;
	mat.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	mat.Ambient  = Color(1.0f, 1.0f, 1.0f);
	mat.Specular = Color(1.0f, 1.0f, 1.0f);

	_model->SetMaterial(mat);

	//! Flag
	_shot_flag = true;
	_move_flag = false;

	return true;
}



