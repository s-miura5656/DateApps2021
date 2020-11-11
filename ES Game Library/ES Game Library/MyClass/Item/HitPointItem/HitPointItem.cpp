#include "HitPointItem.h"

bool HitPointItem::Initialize()
{
	hit_point = 1000.f;

	Material material;
	material.Diffuse = Color(0.0f, 1.0f, 0.0f);
	material.Ambient = Color(0.0f, 1.0f, 0.0f);

	SphereShape();

	sphere->SetMaterial(material);
	
	return true;
}

void HitPointItem::Update()
{

}