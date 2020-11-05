#pragma once
#include "CollisionBase/CollisionBase.h"

class Collision : public CollisionBase
{
public:
	Collision();
	~Collision();

	void SetSize(Vector3& scale) { box->SetScale(scale); }
	void SetPos(Vector3& position) { box->SetPosition(position); }
	OrientedBoundingBox GetCollision() { return hit_box = box->GetOBB(); }

private:
	
};