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

	void SetHitBoxSize(Vector3& scale) { _box->SetScale(scale); }
	void SetHitBoxPos(Vector3& position) { _box->SetPosition(position + Vector3(0, _box->GetScale().y / 2, 0)); }
	void SetHitBoxMaterial(Material& mat) { _box->SetMaterial(mat); }
	void SetAttackHit(bool& hit) { _attack_hit = hit; }

	bool GetAttackHit() { return _attack_hit; }

	OrientedBoundingBox GetBoxCollision() { return _hit_box = _box->GetOBB(); }
private:
	
};