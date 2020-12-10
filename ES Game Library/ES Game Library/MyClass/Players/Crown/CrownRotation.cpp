#include"CrownRotation.h"
#include"../../Data/ModelAnimation.h"
#include"../../Managers/ResouceManager/ResouceManager.h"

CrownRotation::CrownRotation()
{
	_i_player_data = new IPrayerData;
}

CrownRotation::~CrownRotation()
{
	delete _i_player_data;
}

bool CrownRotation::Initialize()
{
	_model = ResouceManager::Instance().LoadModelFile(_T("Crown/crown.X"));
	_effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/crown_effect/star_05.efk"));

	Material material;
	material.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	material.Ambient  = Color(1.0f, 1.0f, 1.0f);
	material.Specular = Color(1.0f, 1.0f, 1.0f);
	material.Power    = 10.0f;

	_model->SetMaterial(material);
	_model->SetScale(0.75f, 0.75f, 0.75f);

	effectnum= _effect->Play(Vector3(0.0f, 0.0f, 0.0f));

	return true;
}

int CrownRotation::Update()
{

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);

		if (_i_player_data->GetRankNum(tag) == 0)
		{
			camp = tag;
			_position = _i_player_data->GetPosition(tag) + Vector3(0, 1.1f, 0);
		}
	}

	auto a = _i_player_data->GetAllParametor();

	ModelRotation(Vector3(0.0f, 3.0f, 0.0f), _model);

	return 0;
}

void CrownRotation::Draw3D()
{
	_model->SetPosition(_position);
	_model->Draw();
	_effect->SetPosition(effectnum, _position + Vector3_Up * 0.1f);
	_effect->SetScale(effectnum, 0.3f);
	
}

