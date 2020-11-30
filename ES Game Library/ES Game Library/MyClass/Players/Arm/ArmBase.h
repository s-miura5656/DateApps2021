#pragma once
#include "../../../ESGLib.h"
#include "../../Data/WordsTable.h"
#include "../../Data/IData.h"
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
	virtual void Draw2D();
	virtual void Draw3D();

	void Move(Controller* pad);
	void ArmReturn();
	void ArmFire();

	int     GetArmState() { return _arm_state; }
	Vector3 ArmGetPos()   { return _model->GetPosition(); }
	MODEL   GetArm()      { return _model; }


protected:
	FONT _font;
	std::string _tag;
	std::string _player_tag;
	
	MODEL _model;

	int _arm_state;

	float scale;
	float _angle = 0.f;
	int _old_angle = INT_MAX;
	float arm_speed;

	bool  hit_flag;

	float _dist;

	std::vector<Vector3> _angle_point;
	Vector3 _position = Vector3_Zero;
	Vector3 _old_pos  = Vector3_Zero;
	Vector3 _new_pos = Vector3_Zero;

	IPrayerData* _iplayer_data;
	IArmData* _iarm_Data;
	IMapData*	 _imap_data;

	
	std::unique_ptr<HitBox> _hit_box;

	IndexNum _index_num;

	bool _move_flag = false;
	float _lerp_count = 0.f;
	int _count = 0;
};
