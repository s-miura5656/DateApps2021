#pragma once
#include "../../../ESGLib.h"

class CollisionBase
{
public:
	CollisionBase();
	virtual ~CollisionBase();

	virtual void Initialize();
	virtual void Draw3D();

protected:
	MODEL box;
	OrientedBoundingBox hit_box;
};
