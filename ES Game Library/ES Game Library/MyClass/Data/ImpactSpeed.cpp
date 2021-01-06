#include"ImpactSpeed.h"

ImpactSpeed::ImpactSpeed()
{
}

ImpactSpeed::~ImpactSpeed()
{
}

//! @param (impact_max) モデルに加わる衝撃値の初期化
//! @param (attenuate_init) 減衰させる値の初期化
bool ImpactSpeed::Initialize(Vector3(impact_power), Vector3(attenuate_init))
{
	impact = impact_power;
	attenuate = Vector3(attenuate_init);

	return true;
}

//! @brief 
//! @param (attenuate_max) 衝撃値から減衰させる値
int ImpactSpeed::Update(Vector3(attenuate_max))
{
	if (impact.x <= 0.0f || impact.y <= 0.0f || impact.x <= 0.0f)
	{
		attenuate = Vector3(attenuate_max);
	}

	return 0;
}

//! @fn モデルに衝撃が加わった際に物理演算風の移動をさせる関数
//! @param (attenuate_up) 減衰を増やす値
//! @param (model) 移動させたいモデル
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
