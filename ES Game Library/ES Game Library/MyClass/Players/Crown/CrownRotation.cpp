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

	//int effect_no = _effect->Play(_model->GetPosition() + Vector3(0.0f, 0.5f, -0.3f));
	//_effect->SetScale(effect_no, 0.3f);

	time = 0.0f;

	camp   = "";
	camp_2 = "";

	effectnum= _effect->Play(Vector3(0.0f, 0.0f, 0.0f));
	//int effect_no;
	//_effect->SetPosition(effect_no, _model->GetPosition() + Vector3(0.0f, 0.5f, -0.3f));
	//int effect_no = _effect->SetScale(effect_no, 0.3f);

	//_effect->SetScale(effect_no, 0.3f);


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
			_position = _i_player_data->GetPosition(tag) + Vector3(0,1.1,0);
		}
		else
		{
			if(_i_player_data->GetRankNum(tag) == 1)
			camp_2 = tag;
		}
		if (_i_player_data->GetRankingPoint(camp) == _i_player_data->GetRankingPoint(camp_2)) {
			_position = Vector3(9999, 9999, 9999);
			break;
		}
	}

	auto a = _i_player_data->GetAllParametor();

	ModelRotation(Vector3(0.0f, 3.0f, 0.0f), _model);

	time += GameTimer.GetElapsedSecond();

	if (time >= 0.75f)
	{
		/*int effect_no = _effect->Play(_model->GetPosition() + Vector3(0.0f, 0.5f, -0.3f));
		_effect->SetScale(effect_no, 0.3f);
		time = 0.0f;*/

	}

	return 0;
}

void CrownRotation::Draw3D()
{
	_model->SetPosition(Vector3(_position));
	_model->Draw();
	_effect->SetPosition(effectnum, _i_player_data->GetPosition(camp) + Vector3(0.0f, 1.25f, 0.0f));
	_effect->SetScale(effectnum, 0.3f);
	
}

