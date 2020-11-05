#pragma once
#include "../../../ESGLib.h"

class CollisionBase
{
private:


protected:
	MODEL box;
	OrientedBoundingBox hit_box;
public:
	CollisionBase();
	virtual ~CollisionBase();

	virtual void Initialize();
	virtual void Update();
	virtual void Draw3D();
};
