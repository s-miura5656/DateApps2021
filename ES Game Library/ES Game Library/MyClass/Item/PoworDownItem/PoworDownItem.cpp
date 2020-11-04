#include "PoworDownItem.h"

bool PoworDownItem::Initialize()
{
	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	material.Ambient = Color(0.5f, 0.5f, 0.5f);
	material.Specular = Color(1.0f, 1.0f, 1.0f);
	material.Emissive = Color(1.0f, 1.0f, 1.0f);
	material.Power = 0.0f;

	model = GraphicsDevice.CreateModelFromFile(_T("Player/sword_01.X"));

	model->SetPosition(Vector3(13, 0, 13));
	model->SetRotation(Vector3(45, 0, 0));
	model->SetScale(0.005f);
	model->SetMaterial(material);

	return true;
}

int PoworDownItem::Update()
{
	return 0;
}

void PoworDownItem::Draw2D()
{
}

void PoworDownItem::Draw3D()
{
	model->Draw();
}
