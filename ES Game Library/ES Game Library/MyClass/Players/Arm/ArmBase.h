#pragma once
#include "../../../ESGLib.h"
#include "../../Data/GameData.h"
#include "../../Data/IPlayerData.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"
#include "../../Collision/HitBox.h"

using namespace PlayerEnum;

class ArmBase
{
public:
	ArmBase();
	virtual ~ArmBase();

	virtual bool Initialize() { return true; }
	virtual int  Update();
	virtual void Draw();

	void    SetPra(Vector3 pos, float angle);
	void    ArmShoot(int flag);
	void    Move(float speed);
	void    MoveProtoType();
	int     GetArmState() { return arm_state; }
	Vector3 ArmGetPos()   { return arm_model->GetPosition(); }
	MODEL   GetArm()      { return arm_model; }

protected:
	std::string _player_tag;
	MODEL arm_model;

	int arm_state;

	float scale;
	float angle;
	float arm_speed;

	bool  hit_flag;

	float dist;

	Vector3 arm_get_pos;
	Vector3 arm_get_rot;

	IPrayerData* _iplayer_data;

	float player_angle;
	
	std::unique_ptr<HitBox> _hit_box;
	std::string _tag;
};
