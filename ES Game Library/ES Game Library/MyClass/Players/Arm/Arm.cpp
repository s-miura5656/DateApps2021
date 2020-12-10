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
	_hit_box->SetHitBoxScale(0.6f);

	_i_player_data.reset(new IPrayerData);
	_i_arm_Data.reset(new IArmData);
	_i_map_data.reset(new IMapData);

	_create_count++;
}

Arm::~Arm()
{
	_angle_positions.clear();
	_i_arm_Data->SetAnglePositions(_tag, _angle_positions);

	_angles.clear();
	_i_arm_Data->SetAngles(_tag, _angles);

	_i_map_data.reset();
	_i_arm_Data.reset();
	_i_player_data.reset();
	_hit_box.reset();
	_shot_effect->Stop(effect_num);

	_create_count--;
}

bool Arm::Initialize()
{
	//! File
	_font		 = ResouceManager::Instance().LordFontFile(_T("SketchFlow Print"), 20);
	_model		 = ResouceManager::Instance().LoadModelFile(_T("Player/robot_arm.X"));

	_shot_effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/roket_punch/roket_punch_fixed.efk"));
	_shader		 = ResouceManager::Instance().LordEffectFile(_T("HLSL/BaseShader.hlsl"));

	effect_num = _shot_effect->Play(_position + Vector3(0, 1, 0));

	//! Angle
	_angle = _i_player_data->GetAngle(_player_tag);
	_old_angle = _angle;
	_angles.push_back(_angle);

	//! Position
	_position = _i_player_data->GetPosition(_player_tag);
	_angle_positions.push_back(_position);
	_old_pos = _position;
	_new_pos = _position;
	_index_num = _i_player_data->GetIndexNum(_player_tag);

	//! hit_box
	SetCollisionPosition();

	//! State
	_arm_state = ArmEnum::PunchState::PUNCH;
	_i_arm_Data->SetState(_tag, _arm_state);

	//! Scale
	_scale = 0;
	_model->SetScale(_scale);

	//! distance
	_player_distance = FLT_MAX;

	//! Material
	Material mat;
	mat.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	mat.Ambient  = Color(1.0f, 1.0f, 1.0f);
	mat.Specular = Color(1.0f, 1.0f, 1.0f);

	_model->SetMaterial(mat);

	//! Flag
	_move_flag = false;
	_turn_flag = false;

	//! texture
	auto path = ConvertFilePath("Player/", _tag, ".png");
	_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
	return true;
}



