#pragma once
#include "../../../ESGLib.h"
#include "../../Data/WordsTable.h"
#include "../../Data/IData.h"
#include "../../Data/StructList.h"
#include "../../Managers/InputManager/InputManager.h"
#include "../../Collision/HitBox.h"
#include "../Wire/Wire.h"

using namespace PlayerEnum;

class ParticleSystem;

class ArmBase
{
public:
	ArmBase();
	virtual ~ArmBase();

	virtual bool Initialize() { return true; }
	virtual int  Update();
	virtual void Draw2D();
	virtual void Draw3D();

protected:
	void MoveArm(BaseInput* pad);
	bool TurnArm(BaseInput* pad);
	void ArmReturn();
	void HitOtherObject();
	void SetCollisionPosition();
	void ChangeDirection(BaseInput* pad);

	//! file
	FONT	  _font;
	MODEL	  _model;
	EFFECT    _shader;
	SPRITE	  _texture;

	//! tag
	std::string _tag;
	std::string _player_tag;
	
	//! state
	int _arm_state;

	//! transform
	Transform _transform;
	
	//! rotation
	int   _old_angle = INT_MAX;
	std::vector<float> _angles;

	//! distnace
	float _player_distance;

	//! position
	std::vector<Vector3> _angle_positions;
	Vector3 _old_pos  = Vector3_Zero;
	Vector3 _new_pos  = Vector3_Zero;

	//! scale
	float _scale;

	//! pointer
	std::unique_ptr<IPrayerData>	_i_player_data;
	std::unique_ptr<IArmData> 		_i_arm_Data;
	std::unique_ptr<IMapData> 		_i_map_data;
	std::unique_ptr<HitBox>			_hit_box;
	std::unique_ptr<ParticleSystem> _shot_effect;
	std::unique_ptr<ParticleSystem> _wall_hit_effect;
	std::vector<std::unique_ptr<Wire>> _wires;

	//! index
	IndexNum _index_num;

	//! count
	float _lerp_count = 0.f;
	int   _wait_count = 0;
	float _scale_count = 0.f;
	int effect_num;

	//! flag
	bool _move_flag;
	bool _turn_flag;

	//! material
	Material _model_material;
private:
	void CreateWire();
	void DeleteWire();

};
