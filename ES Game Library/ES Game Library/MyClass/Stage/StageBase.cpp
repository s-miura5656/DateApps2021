#include "StageBase.h"

StageBase::StageBase()
{

}

StageBase::~StageBase()
{

}

int StageBase::Update()
{
    return 0;
}

void StageBase::Draw3D()
{
	_model->SetPosition(_position);
	_model->SetRotation(0,0,0);
	_model->Draw();

	if (_hit_box != nullptr)
	{
		//_hit_box->Draw3D();
	}
}

void StageBase::DrawAlpha3D()
{
}

Material StageBase::GetMaterial()
{
    Material temp = Material();

	temp.Diffuse  = Color(0.5f, 0.5f, 0.5f);
	temp.Ambient  = Color(0.25f, 0.25f, 0.25f);
	temp.Specular = Color(0.5f, 0.5f, 0.5f);
	temp.Power	  = 0.0f;

	return temp;
}
