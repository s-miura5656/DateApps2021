#include"CrownRotation.h"
#include"../../Data/ModelAnimation.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include "../../ParticleSystem/Particle.h"
#include "../../Managers/SceneManager/SceneManager.h"

CrownRotation::CrownRotation()
{
	_i_player_data = new IPrayerData;
	_effect.reset(new ParticleSystem);
}

CrownRotation::~CrownRotation()
{
	_effect.reset();
	delete _i_player_data;
}

bool CrownRotation::Initialize()
{
	_model = ResouceManager::Instance().LoadModelFile(_T("Crown/crown.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StandardShader.hlsl"));
	auto effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/crown_effect/star_05.efk"));

	_effect->RegisterParticle(effect);

	_model_material.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	_model_material.Ambient  = Color(1.0f, 1.0f, 1.0f);
	_model_material.Specular = Color(1.0f, 1.0f, 1.0f);
	_model_material.Power    = 10.0f;

	_model->SetScale(0.75f, 0.75f, 0.75f);

	_effect->SetScale(0.3f);

	crown_flag = false;

	rankingpoint_max = 0;
	rankingpoint_min = 0;

	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);

	return true;
}

int CrownRotation::Update()
{
	auto param_list = _i_player_data->GetAllParametor();
		for (int i = 0; i < PLAYER_COUNT_MAX; i++)
		{
			std::string tag = PLAYER_TAG + std::to_string(i + 1);
			if (rankingpoint_max < param_list[tag].ranking_point) 
			{
				crown_flag = true;
			}
			
			if (_i_player_data->GetRankNum(tag) == 0)
			{
				_position = _i_player_data->GetPosition(tag) + Vector3(0, 1.1f, 0);
			}
		}

		ModelRotation(Vector3(0.0f, 3.0f, 0.0f), _model);
		_effect->SetPosition(_position + Vector3_Up * 0.1f);

	return 0;
}

void CrownRotation::Draw3D()
{
	_model->SetPosition(_position);
	_model->SetMaterial(_model_material);

	if (crown_flag)
	{
		auto camera = SceneCamera::Instance().GetCamera();
		Matrix world = _model->GetWorldMatrix();
		_shader->SetParameter("model_ambient", _model_material.Ambient);
		_shader->SetParameter("wvp", world * camera.GetViewProjectionMatrix());
		_shader->SetParameter("eye_pos", camera.GetPosition());
		_shader->SetTechnique("FixModel_S0");
		_model->Draw(_shader);
		_effect->PlayOneShot();
		_effect->Draw();
	}
}

