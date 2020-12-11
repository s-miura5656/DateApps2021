#include"CrownRotation.h"
#include"../../Data/ModelAnimation.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include "../../ParticleSystem/Particle.h"

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
	auto effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/crown_effect/star_05.efk"));

	_effect->RegisterParticle(effect);

	Material material;
	material.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	material.Ambient  = Color(1.0f, 1.0f, 1.0f);
	material.Specular = Color(1.0f, 1.0f, 1.0f);
	material.Power    = 10.0f;

	_model->SetMaterial(material);
	_model->SetScale(0.75f, 0.75f, 0.75f);

	_effect->SetScale(0.3f);
	_effect->Play();

	crown_flag = false;

	rankingpoint_max = 0;
	rankingpoint_min = 0;

	return true;
}

int CrownRotation::Update()
{
	auto param_list = _i_player_data->GetAllParametor();
		for (int i = 0; i < PLAYER_COUNT_MAX; i++)
		{
			std::string tag = PLAYER_TAG + std::to_string(i + 1);
			if (rankingpoint_max < param_list[tag].ranking_point) {
				/*float point = rankingpoint_max;
				rankingpoint_max = param_list[tag].ranking_point;
				rankingpoint_min = point;*/
				crown_flag = true;
			}
			/*else if (rankingpoint_max == param_list[tag].ranking_point)
			{
				rankingpoint_min = param_list[tag].ranking_point;

			}*/
			
			


			/*if(param_list[tag].ranking_point == param_list[tag2].ranking_point)*/
		
		
			if (_i_player_data->GetRankNum(tag) == 0)
			{
				_position = _i_player_data->GetPosition(tag) + Vector3(0, 1.1f, 0);
			}
			

		}


	/*	if (rankingpoint_max == rankingpoint_min)
			crown_flag = false;
		else
			crown_flag = true;*/
		
		
		ModelRotation(Vector3(0.0f, 3.0f, 0.0f), _model);
		_effect->SetPosition(_position + Vector3_Up * 0.1f);

	return 0;
}

void CrownRotation::Draw3D()
{
	_model->SetPosition(_position);

	if (crown_flag)
	{
		_model->Draw();
		_effect->Draw();
	}
}

