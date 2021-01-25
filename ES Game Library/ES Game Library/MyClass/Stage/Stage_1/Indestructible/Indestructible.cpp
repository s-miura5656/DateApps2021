#include"Indestructible.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Managers/SceneManager/SceneManager.h"

Indestructible::Indestructible()
{
	_model = nullptr;
}

Indestructible::~Indestructible()
{

}

bool Indestructible::Initialize()
{
	//Xファイルの読み込み
	_model  = ResouceManager::Instance().LoadModelFile(_T("MapSprite/Stage/stage plan A_v2.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StandardShader.hlsl"));

	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定

	_model_material.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	_model_material.Ambient  = Color(0.25f, 0.25f, 0.25f);
	_model_material.Specular = Color(1.0f, 1.0f, 1.0f);

	
	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);

	return _model != nullptr;
}

void Indestructible::Draw3D()
{
	_model->SetPosition(_position);
	_model->SetRotation(0, 0, 0);
	_model->SetMaterial(_model_material);

	auto camera = SceneCamera::Instance().GetCamera();
	Matrix world = _model->GetWorldMatrix();
	_shader->SetParameter("model_ambient", _model_material.Ambient);
	_shader->SetParameter("wvp", world * camera.GetViewProjectionMatrix());
	_shader->SetParameter("eye_pos", camera.GetPosition());
	_shader->SetTechnique("FixModel_S0");
	_model->Draw(_shader);
}
