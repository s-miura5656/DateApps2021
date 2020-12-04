#include"ImpactSpeed.h"

bool ImpactSpeed::Initialize(Vector3(attenuate_init))
{

	impact = Vector3_Zero;;
	attenuate = Vector3(attenuate_init);

	return true;
}

int ImpactSpeed::Update(Vector3(impact_max), Vector3(attenuate_max))
{

	if (impact.x <= 0.0f || impact.y <= 0.0f || impact.x <= 0.0f)
	{
		impact = Vector3(impact_max);
		attenuate = Vector3(attenuate_max);
	}

	return 0;
}

void ImpactSpeed::impactSpeed(Vector3(attenuate_up), MODEL model)
{

	Vector3 pos = model->GetPosition();
	pos += impact;
	model->SetPosition(pos);
	impact -= attenuate;
	attenuate += Vector3(attenuate_up);
	if (impact.x < 0.0f || impact.y < 0.0f || impact.z < 0.0f)
	{
		impact.x = 0.0f;
		impact.y = 0.0f;
		impact.z = 0.0f;
	}
}
