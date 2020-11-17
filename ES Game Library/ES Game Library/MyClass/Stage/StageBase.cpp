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
	_model->SetRotation(0, 0, 0);
	_model->Draw();
}

Material StageBase::GetMaterial()
{
    Material temp = Material();

	temp.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	temp.Ambient  = Color(1.0f, 1.0f, 1.0f);
	temp.Specular = Color(1.0f, 1.0f, 1.0f);
	temp.Power	  = 0.0f;

	return temp;
}
