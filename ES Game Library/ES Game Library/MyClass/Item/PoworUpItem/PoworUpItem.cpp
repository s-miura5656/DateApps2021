#include "PoworUpItem.h"

bool PoworUpItem::Initialize()
{
	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	material.Ambient = Color(0.5f, 0.5f, 0.5f);
	material.Specular = Color(1.0f, 1.0f, 1.0f);
	material.Emissive = Color(1.0f, 1.0f, 1.0f);
	material.Power = 0.0f;

	model = GraphicsDevice.CreateModelFromFile(_T("Player/robot_02.X"));
	
	model->SetPosition(Vector3(1, 0, 13));
	model->SetRotation(Vector3(45, 0, 0));
	model->SetScale(0.005f);
	model->SetMaterial(material);


	return true;
}

int PoworUpItem::Update()
{
	return 0;
}

void PoworUpItem::Draw2D()
{
}

void PoworUpItem::Draw3D()
{
	model->Draw();
}
