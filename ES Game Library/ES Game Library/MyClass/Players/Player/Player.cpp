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
	_player_speedup_effect.reset(new ParticleSystem);
	_arm_speedup_effect.reset(new ParticleSystem);
	_powerdown_effect.reset(new ParticleSystem);
	_thunder_effect.reset(new ParticleSystem);
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
	_font                  = ResouceManager::Instance().LordFontFile(_T("UD デジタル 教科書体 NK-B"), 30);
	_model                 = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	_shader		           = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	auto&& effect          = ResouceManager::Instance().LordEffekseerFile(_T("Effect/damage_effect01/damege_0127.efk"));
	auto&& playerspeedup   = ResouceManager::Instance().LordEffekseerFile(_T("Effect/Player_Effect/Speedup_Aura_01/speedup_aura_01.efk"));
	auto&& armspeedup      = ResouceManager::Instance().LordEffekseerFile(_T("Effect/Player_Effect/Arm_Aura/arm_aura_02.efk"));
	auto&& powerdown       = ResouceManager::Instance().LordEffekseerFile(_T("Effect/Player_Effect/DebuffAura/debuff_aura_01.efk"));
	auto&& thunder         = ResouceManager::Instance().LordEffekseerFile(_T("Effect/Player_Effect/Thunder_Aura/thunder_aura.efk"));

	//! Position
	_model->SetPosition(_i_player_data->GetPosition(_tag));
	_transform.position = _model->GetPosition();
	_old_pos = _transform.position;
	_new_pos = _transform.position;
	_index_num.Initialize(fabsf(_transform.position.x), fabsf(_transform.position.y), fabsf(_transform.position.z));
	_i_player_data->SetIndexNum(_tag, _index_num);

	//! Scale
	_model->SetScale(_transform.scale);

	//! rotation
	_transform.rotation.y = _i_player_data->GetAngle(_tag);
	_old_angle = _transform.rotation.y;

	//! hit_box
	SetCollisionPosition();

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
	_destroy_effect->SetScale(3.0f);

	_player_speedup_effect->RegisterParticle(playerspeedup);
	_player_speedup_effect->SetNomalEffect();

	_arm_speedup_effect->RegisterParticle(armspeedup);
	_arm_speedup_effect->SetNomalEffect();
	_arm_speedup_effect->SetScale(2.0f);

	_powerdown_effect->RegisterParticle(powerdown);
	_powerdown_effect->SetNomalEffect();

	_thunder_effect->RegisterParticle(thunder);
	_thunder_effect->SetNomalEffect();
	_thunder_effect->SetScale(0.5f);

	_effect.insert(std::make_pair(ITEM_PLAYER_SPEEDUP, std::move(_player_speedup_effect)));
	_effect.insert(std::make_pair(ITEM_ARM_SPEEDUP, std::move(_arm_speedup_effect)));
	_effect.insert(std::make_pair(ITEM_POWERDOWN, std::move(_powerdown_effect)));
	_effect.insert(std::make_pair(ITEM_THUNDER, std::move(_thunder_effect)));

	//! collision
	_hit_box->Init();
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(0.6f);
	_hit_box->SetPlayerBase(this);

	//! shader
	_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");
	std::string player_number = PLAYER_TAG + to_string(SceneManager::Instance().GetPlayerTexture(_tag));
	auto path = ConvertFilePath("Player/", player_number, ".png");
	_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);
	return true;
}





