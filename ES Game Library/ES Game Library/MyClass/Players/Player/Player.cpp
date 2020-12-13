#include "Player.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Data/Parametor.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include "../../Managers/SceneManager/SceneManager.h"
#include "../../ParticleSystem/Particle.h"
#include <codecvt>

Player::Player(std::string tag)
{
	_tag = tag;
	_arm_tag = ARM_TAG + std::to_string(GetTagNum(tag));
	
	_hit_box.reset(new HitBox());
	_destroy_effect.reset(new ParticleSystem);
	_i_player_data.reset(new IPrayerData);
	_i_arm_Data.reset(new IArmData);
	_i_map_data.reset(new IMapData);
}

Player::~Player()
{
	_arm.reset();
	_i_map_data.reset();
	_i_arm_Data.reset();
	_i_player_data.reset();
	_destroy_effect.reset();
	_hit_box.reset();
}

bool Player::Initialize()
{
	//! file
	_font			= ResouceManager::Instance().LordFontFile(_T("SketchFlow Print"), 20);
	_model			= ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	_shader			= ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	_wire_shader	= ResouceManager::Instance().LordEffectFile(_T("HLSL/WireShader.hlsl"));
	auto&& effect   = ResouceManager::Instance().LordEffekseerFile(_T("Effect/damage_effect01/damage_effect02.efk"));

	for (int i = 0; i < _i_arm_Data->GetLimitRange(_arm_tag); ++i)
	{
		_wire_models.push_back(ResouceManager::Instance().LoadModelFile(_T("Player/wire.X")));
		_wire_models[i]->SetScale(1.0f);
	}

	//! Position
	_model->SetPosition(_i_player_data->GetPosition(_tag));
	_transform.position = _model->GetPosition();
	_old_pos = _transform.position;
	_new_pos = _transform.position;
	_index_num.Initialize(fabsf(_transform.position.x), fabsf(_transform.position.y), fabsf(_transform.position.z));
	_i_player_data->SetIndexNum(_tag, _index_num);

	//! Scale
	_model->SetScale(_transform.scale);

	//! hit_box
	SetCollisionPosition();

	//! Pad
	ControllerManager::Instance().CreateGamePad(_tag);

	//! index
	_animation_index = _i_player_data->GetState(_tag);

	//! count
	_animation_count = 0;

	//! material
	_model_material.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	_model_material.Ambient  = Color(0.9f, 0.9f, 0.9f);
	_model_material.Specular = Color(1.0f, 1.0f, 1.0f);

	//! effect
	_destroy_effect->RegisterParticle(effect);
	_destroy_effect->SetSpeed(1.0f);
	_destroy_effect->SetScale(1.0f);

	//! collision
	_hit_box->Init();
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(0.6f);

	//! shader
	_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");
	auto path = ConvertFilePath("Player/", _tag, ".png");
	_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);

	path = ConvertFilePath("Player/", "wire", ".png");
	_wire_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());

	return true;
}




