#pragma once
#include "../../../ESGLib.h"
#include "../../Enum/Enum.h"
#include "../../Data/IPlayerData.h"

class ArmBase
{
public:
	ArmBase();
	virtual ~ArmBase();

	virtual bool Initialize() { return true; }
	virtual int  Update();
	virtual int  Shoot() { return 0; }
	virtual void Draw();

	//OrientedBoundingBox ArmGetObb() { return arm_obb; }
	void SetPra(Vector3 pos, float angle);
	void ArmShoot(int flag);
	int GetArmState() { return arm_state; }
	Vector3 ArmGetPos() { return arm_model->GetPosition(); }

	MODEL GetArm() { return arm_model; }

protected:
	std::string player_name;
	MODEL arm_model;

	int   arm_state;

	float scale;
	float angle;
	float arm_speed;

	float dist;

	SimpleShape shape;

	Vector3 arm_get_pos;
	Vector3 arm_get_rot;

	IPrayerData* _iplayer_data;
	//MODEL arm_hitbox;
	//OrientedBoundingBox arm_obb;
	
};
