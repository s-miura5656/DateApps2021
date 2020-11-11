#include "SpeedItem.h"

bool SpeedItem::Initialize()
{
	_speed = 50.f;

	Material material;
	material.Diffuse = Color(0.0f, 0.0f, 1.0f);
	material.Ambient = Color(0.0f, 0.0f, 1.0f);

	SphereShape();

	_sphere->SetMaterial(material);

	return true;
}

bool SpeedItem::Update()
{
	return true;
}