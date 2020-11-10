#include "../../../ESGLib.h"
#include "../../Enum/Enum.h"

class RocketPunchBase
{
public:
	RocketPunchBase();
	virtual ~RocketPunchBase();

	virtual bool Initialize() { return true; }
	virtual int Update() { return 0; }
	virtual void Draw2D();
	virtual void Draw3D();

	OrientedBoundingBox RocketPunchBaseGetObb() { return rocket_punch_obb; }
	
	Vector3 RocketPunchGetPos() { return rocket_punch->GetPosition(); }

	MODEL GetRocketPunch() { return rocket_punch; }

protected:
	MODEL rocket_punch;

	float scale;
	float angle;
	
	SimpleShape shape;

	MODEL rocket_punch_hitbox;
	OrientedBoundingBox rocket_punch_obb;
	
};
