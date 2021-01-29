#include"Warp.h"
#include "../../../Data/WordsTable.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Data/IData.h"
#include "../../../Players/PlayerBase.h"
#include "../../../Managers/SceneManager/SceneManager.h"
Warp::Warp(std::string tag)
{
	_model = nullptr;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(tag);
	_hit_box->SetHitBox(1, 1, 1);
}

Warp::~Warp()
{
	_hit_box.reset();
}

bool Warp::Initialize()
{
	//Xファイルの読み込み
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/warp.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StandardShader.hlsl"));

	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());

	_hit_box->SetHitBoxPosition(_position);

	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);
	return _model != nullptr;
}
int Warp::Update()
{
	_position.y -= 0.01;
	if (_position.y <= 0.1)
	{
		_position.y = 0.1;
		for (int i = 0; i < PLAYER_COUNT_MAX; i++)
		{
			std::string player_tag = PLAYER_TAG + std::to_string(i + 1);

			if (!_hit_box->Tag_Sarch(player_tag))
			{
				continue;
			}

			if (_hit_box->IsHitObjectsSquare(player_tag))
			{
				Vector3 new_pos = Vector3(0, 0, 0);
				if (_position.x == 1)
				{
					new_pos = Vector3(13, 0, -6);
				}
				else if (_position.x == 13)
				{
					new_pos = Vector3(1, 0, -6);
				}
				_hit_box->GetHitBoxTag(player_tag)->GetPlayerBase()->Warp(new_pos);
			}
		}
	}

	return 0;
}

void Warp::Draw3D()
{
	_hit_box->SetHitBoxPosition(_position);
	_model->SetPosition(_position);

	auto camera = SceneCamera::Instance().GetCamera();
	Matrix world = _model->GetWorldMatrix();
	_shader->SetParameter("model_ambient", _model_material.Ambient);
	_shader->SetParameter("wvp", world * camera.GetViewProjectionMatrix());
	_shader->SetParameter("eye_pos", camera.GetPosition());
	_shader->SetTechnique("FixModel_S0");
	_model->Draw(_shader);
}

