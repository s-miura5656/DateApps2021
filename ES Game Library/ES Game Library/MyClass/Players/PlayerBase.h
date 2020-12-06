#include "../../ESGLib.h"
#include "Arm/Arm.h"
#include "../Collision/HitBox.h"
#include "../Data/IData.h"
#include "../Managers/ControllerManager/ContorollerManager.h"

class PlayerBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

	virtual bool Initialize() { return true; }
	virtual int Update() { return 0; }
	virtual void Draw2D();
	virtual void Draw3D();

	Vector3 GetPos()  { return _model->GetPosition(); }
	float GetAngle()  { return _angle; }
	ANIMATIONMODEL GetPlayer() { return _model; }
	
	void ChangeAnimation();
	void CreateArm();
	void DestroyArm();
	void Move(Controller* pad);

	std::string GetTag() const { return _tag; }
	int GetPlayerNumber() const { return (*_tag.rbegin()) - '0'; }

protected:
	//! file
	ANIMATIONMODEL _model;
	FONT _font;
	EFFECT _shader;
	SPRITE _texture;

	//! transform
	const float scale		 = 0.004f;
	const float player_scale = 1.f;
	float _angle			 = 0.f;
	float _speed			 = 0.f;
	float _move_speed		 = 0.f;
	float _distance			 = FLT_MAX;

	//! position
	Vector3 _position		 = Vector3_Zero;
	Vector3 _old_pos		 = Vector3_Zero;
	Vector3 _new_pos		 = Vector3_Zero;

	//! pointer
	std::unique_ptr<ArmBase> _arm;
	std::unique_ptr<HitBox> _hit_box;
	IPrayerData* _i_player_data;
	IArmData* _i_arm_Data;
	IMapData* _i_map_data;

	//! tag
	std::string _tag;
	std::string _arm_tag;

	//! index
	IndexNum _index_num;
	int _animation_index;

	//! flag 
	bool _move_flag = false;

	//! count
	float _lerp_count       = 0.f;
	int _damage_count       = 0;
	double _animation_count = 0;
	int _shot_pending_count = 0;
};
