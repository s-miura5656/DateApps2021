#include "Arm.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include "../../ParticleSystem/Particle.h"
#include "../../Managers/SceneManager/SceneManager.h"

Arm::Arm(std::string name)
{
	//! tag
	_player_tag = name;
	int arm_num = GetTagNum(name);
	_tag = ARM_TAG + std::to_string(arm_num);

	//! pointer
	_hit_box.reset(new HitBox());
	_i_player_data.reset(new IPrayerData);
	_i_arm_Data.reset(new IArmData);
	_i_map_data.reset(new IMapData);
	_shot_effect.reset(new ParticleSystem);
}

Arm::~Arm()
{
	_angle_positions.clear();
	_i_arm_Data->SetAnglePositions(_tag, _angle_positions);
	_angles.clear();
	_i_arm_Data->SetAngles(_tag, _angles);

	_shot_effect->Stop();

	_shot_effect.reset();
	_i_map_data.reset();
	_i_arm_Data.reset();
	_i_player_data.reset();
	_hit_box.reset();
}

bool Arm::Initialize()
{
	//! File
	_font		  = ResouceManager::Instance().LordFontFile(_T("SketchFlow Print"), 20);
	_model		  = ResouceManager::Instance().LoadModelFile(_T("Player/R_arm.X"));
	auto&& effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/roket_punch/roket_punch_fixed.efk"));
	_shader		  = ResouceManager::Instance().LordEffectFile(_T("HLSL/StandardShader.hlsl"));

	//! Angle
	_transform.rotation.y = _i_player_data->GetAngle(_player_tag);
	_old_angle = _transform.rotation.y;
	_angles.push_back(_transform.rotation.y);

	//! Position
	_transform.position = _i_player_data->GetPosition(_player_tag) + Vector3(0, 0.5f, 0);
	_angle_positions.push_back(_transform.position);
	_old_pos = _transform.position;
	_new_pos = _transform.position;
	_index_num = _i_player_data->GetIndexNum(_player_tag);

	//! hit_box
	SetCollisionPosition();

	//! State
	_arm_state = ArmEnum::PunchState::PUNCH;
	_i_arm_Data->SetState(_tag, _arm_state);

	//! effect
	_shot_effect->RegisterParticle(effect);
	_shot_effect->SetSpeed(1.0f);
	_shot_effect->SetScale(1.0f);
	_shot_effect->Play();

	//! Scale
	_scale = 0;
	_model->SetScale(_scale);

	//! distance
	_player_distance = FLT_MAX;

	//! Material
	_model_material.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	_model_material.Ambient  = Color(1.0f, 1.0f, 1.0f);
	_model_material.Specular = Color(1.0f, 1.0f, 1.0f);

	//! collision
	_hit_box->Init();
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(0.6f);

	//! Flag
	_move_flag = false;
	_turn_flag = false;

	//! texture
	auto path = ConvertFilePath("Player/", _tag, ".png");
	_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());

	//! shader
	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);
	return true;
}



