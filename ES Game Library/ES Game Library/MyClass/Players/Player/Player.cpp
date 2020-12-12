#include "Player.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Data/Parametor.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include "../../Managers/SceneManager/SceneManager.h"
#include <codecvt>

Player::Player(std::string tag)
{
	PlayerParametor::Instance().CreateParametor(tag);
	
	_tag = tag;
	_arm_tag = ARM_TAG + std::to_string(GetTagNum(tag));
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(tag);
	_hit_box->SetHitBoxScale(0.6f);
	_i_player_data = new IPrayerData;
	_i_arm_Data    = new IArmData;
	_i_map_data    = new IMapData;
}

Player::~Player()
{
	_arm.reset();
	delete _i_map_data;
	delete _i_arm_Data;
	delete _i_player_data;
	_hit_box.reset();
}

bool Player::Initialize()
{
	//! file
	_font			= ResouceManager::Instance().LordFontFile(_T("SketchFlow Print"), 20);
	_model			= ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	_shader			= ResouceManager::Instance().LordEffectFile(_T("HLSL/CharaShader.hlsl"));
	_wire_shader	= ResouceManager::Instance().LordEffectFile(_T("HLSL/WireShader.hlsl"));
	_destroy_effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/damage_effect01/damage_effect02.efk"));

	for (int i = 0; i < _i_arm_Data->GetLimitRange(_arm_tag); ++i)
	{
		_wire_models.push_back(ResouceManager::Instance().LoadModelFile(_T("Player/wire.X")));
		_wire_models[i]->SetScale(1.0f);
	}

	//! Position
	_model->SetPosition(_i_player_data->GetPosition(_tag));
	_position = _model->GetPosition();
	_old_pos = _position;
	_new_pos = _position;
	_index_num.Initialize(fabsf(_position.x), fabsf(_position.y), fabsf(_position.z));
	_i_player_data->SetIndexNum(_tag, _index_num);

	//! Scale
	_model->SetScale(player_scale);

	//! hit_box
	SetCollisionPosition();

	//! Pad
	ControllerManager::Instance().CreateGamePad(_tag);

	//! index
	_animation_index = _i_player_data->GetState(_tag);
	_handle = INT_MAX;

	//! count
	_animation_count = 0;

	//! material
	_model_material.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	_model_material.Ambient  = Color(0.9f, 0.9f, 0.9f);
	_model_material.Specular = Color(1.0f, 1.0f, 1.0f);

	//! shader
	_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");
	auto path = ConvertFilePath("Player/", _tag, ".png");
	_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);

	path = ConvertFilePath("Player/", "wire", ".png");
	_wire_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());

	return true;
}




