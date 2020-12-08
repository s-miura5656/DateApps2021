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

	void MoveArm(Controller* pad);
	bool TurnArm(Controller* pad);
	void ArmReturn();
	void HitOtherObject();
protected:

	//! file
	FONT  _font;
	MODEL _model;
	EFFEKSEER _shot_effect;

	//! tag
	std::string _tag;
	std::string _player_tag;
	
	//! state
	int _arm_state;

	//! rotation
	float _angle = 0.f;
	int   _old_angle = INT_MAX;

	//! distnace
	float _player_distance;

	//! position
	std::vector<Vector3> _angle_point;
	Vector3 _position = Vector3_Zero;
	Vector3 _old_pos  = Vector3_Zero;
	Vector3 _new_pos  = Vector3_Zero;

	//! pointer
	std::unique_ptr<IPrayerData> _i_player_data;
	std::unique_ptr<IArmData> 	 _i_arm_Data;
	std::unique_ptr<IMapData> 	 _i_map_data;
	std::unique_ptr<HitBox> _hit_box;

	//! index
	IndexNum _index_num;

	//! count
	float _lerp_count = 0.f;
	int   _wait_count = 0;
	static int _create_count;
	int effect_num;

	//! flag
	bool _move_flag;
	bool _turn_flag;
};
