#include"CrownRotation.h"
#include"../../Data/ModelAnimation.h"
#include"../../Managers/ResouceManager/ResouceManager.h"

bool CrownRotation::Initialize()
{

	_model = GraphicsDevice.CreateModelFromFile(_T("Crown/crown.X"));
	_effect = Effekseer.CreateEffectFromFile(_T("crown_effect/star_04.efk"));

	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	material.Ambient = Color(1.0f, 1.0f, 1.0f);
	material.Specular = Color(1.0f, 1.0f, 1.0f);
	material.Power = 10.0f;

	_model->SetMaterial(material);
	
	_model->SetScale(1.0f, 1.0f, 1.0f);

	int effect_no = _effect->Play(_model->GetPosition() + Vector3(0.0f, 0.5f, -0.3f));
	_effect->SetScale(effect_no, 0.3f);
	time = 0.0f;

	return true;
}

int CrownRotation::Update()
{

	ModelRotation(Vector3(0.0f, 3.0f, 0.0f), _model);
	
	//Effekseer.Update();

	time += GameTimer.GetElapsedSecond();
	if (time >= 0.75f) 
	{
		int effect_no = _effect->Play(_model->GetPosition() + Vector3(0.0f, 0.5f, -0.3f));
		_effect->SetScale(effect_no, 0.3f);
		time = 0.0f;
	}

	return 0;
}

void CrownRotation::Draw3D()
{
	_model->Draw();
	//Effekseer.Draw();
}

//void CrownRotation::SetPosition(Vector3 position)
//{
//	_model->SetPosition(Vector3(position));
//}
