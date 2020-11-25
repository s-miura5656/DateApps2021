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
	_model->SetRotation(_rotation);
	_model->Draw();

	if (_hit_box != nullptr)
	{
		_hit_box->Draw3D();
	}
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
