#include "SpeedItem.h"

bool SpeedItem::Initialize()
{
	speed = 50.f;

	Material material;
	material.Diffuse = Color(0.0f, 0.0f, 1.0f);
	material.Ambient = Color(0.0f, 0.0f, 1.0f);

	SphereShape();

	sphere->SetMaterial(material);

	return true;
}

void SpeedItem::Update()
{

}