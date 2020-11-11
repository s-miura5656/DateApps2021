#include "AttackPowerItem.h"

bool AttackPowerItem::Initialize()
{
	attack_powor = 100.f;
	
	Material material;
	material.Diffuse = Color(1.0f, 0.0f, 0.0f);
	material.Ambient = Color(1.0f, 0.0f, 0.0f);

	SphereShape();

	sphere->SetMaterial(material);

	return true;
}

void AttackPowerItem::Update()
{

}