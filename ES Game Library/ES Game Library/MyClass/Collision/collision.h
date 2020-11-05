//! @file   Collision.h
//! @brief  �����蔻��p�̎q�N���X
//! @author Souta_Miura
//! @date   2020/11/05
#pragma once
#include "../Collision/CollisionBase.h"

class Collision : public CollisionBase
{
public:
	Collision();
	~Collision();

	void Initialize();

	void SetHitBoxSize(Vector3& scale) { box->SetScale(scale); }
	void SetHitBoxPos(Vector3& position) { box->SetPosition(position); }
	void SetHitBoxMaterial(Material& mat) { box->SetMaterial(mat); }
	
	OrientedBoundingBox GetBoxCollision() { return hit_box = box->GetOBB(); }
private:
	
};