#include"ImpactSpeed.h"

ImpactSpeed::ImpactSpeed()
{
}

ImpactSpeed::~ImpactSpeed()
{
}

//! @param (impact_max) ���f���ɉ����Ռ��l�̏�����
//! @param (attenuate_init) ����������l�̏�����
bool ImpactSpeed::Initialize(Vector3(impact_power), Vector3(attenuate_init))
{
	impact = impact_power;
	attenuate = Vector3(attenuate_init);

	return true;
}

//! @brief 
//! @param (attenuate_max) �Ռ��l���猸��������l
int ImpactSpeed::Update(Vector3(attenuate_max))
{
	if (impact.x <= 0.0f || impact.y <= 0.0f || impact.x <= 0.0f)
	{
		attenuate = Vector3(attenuate_max);
	}

	return 0;
}

//! @fn ���f���ɏՌ�����������ۂɕ������Z���̈ړ���������֐�
//! @param (attenuate_up) �����𑝂₷�l
//! @param (model) �ړ������������f��
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
