#pragma once
#include "../../../ESGLib.h"
#include "../../Enum/Enum.h"

class ArmBase
{
public:
	ArmBase();
	virtual ~ArmBase();

	virtual bool Initialize() { return true; }
	virtual int  Update() { return 0; }
	virtual int  Shoot() { return 0; }
	virtual void Draw();

	//OrientedBoundingBox ArmGetObb() { return arm_obb; }
	
	Vector3 ArmGetPos() { return arm_model->GetPosition(); }

	MODEL GetArm() { return arm_model; }

protected:
	MODEL arm_model;

	int   arm_state;

	float scale;
	float angle;
	float arm_speed;

	float dist;

	SimpleShape shape;

	//MODEL arm_hitbox;
	//OrientedBoundingBox arm_obb;
	
};
