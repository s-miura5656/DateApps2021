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
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/stage.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StageShader.hlsl"));

	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());
	
	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);
	_shader->SetParameter("model_ambient", _model->GetMaterial().Ambient);

	return _model != nullptr;
}

void Indestructible::Draw3D()
{
	_model->SetPosition(_position);
	_model->SetRotation(0, 0, 0);

	Matrix world = _model->GetWorldMatrix();
	_shader->SetParameter("wvp", world * SceneCamera::Instance().GetCamera().GetViewProjectionMatrix());
	_shader->SetParameter("eye_pos", SceneCamera::Instance().GetCamera().GetPosition());
	_model->Draw(_shader);
}
