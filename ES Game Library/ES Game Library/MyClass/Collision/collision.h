//! @file   Collision.h
//! @brief  当たり判定用の子クラス
//! @author Souta_Miura
//! @date   2020/11/05
#pragma once
#include "../Collision/CollisionBase.h"

class Collision : public CollisionBase
{
public:
	Collision();
	~Collision();

	bool Initialize();

	void SetHitBoxSize(Vector3& scale) { box->SetScale(scale); }
	void SetHitBoxPos(Vector3& position) { box->SetPosition(position + Vector3(0, box->GetScale().y / 2, 0)); }
	void SetHitBoxMaterial(Material& mat) { box->SetMaterial(mat); }
	void SetAttackHit(bool& hit) { attack_hit = hit; }

	bool GetAttackHit() { return attack_hit; }

	OrientedBoundingBox GetBoxCollision() { return hit_box = box->GetOBB(); }
private:
	
};