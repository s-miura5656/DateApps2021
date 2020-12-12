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
	virtual int  Update();
	virtual void Draw2D();
	virtual void Draw3D();
	virtual void DrawAlpha3D();

protected:
	//! function
	void DrawModel();
	void DrawWireModel();
	void ChangeAnimation();
	void CreateArm();
	void DestroyArm();
	void Move(Controller* pad);
	void SetCollisionPosition();
	void DebugControll();
	//! file
	ANIMATIONMODEL		_model;
	FONT				_font;
	EFFECT				_shader;
	EFFECT              _wire_shader;
	SPRITE				_texture;
	SPRITE				_wire_texture;
	std::vector<MODEL>  _wire_models;
	EFFEKSEER			_destroy_effect;

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
	int _handle;

	//! flag 
	bool _move_flag  = false;
	bool _flag       = false;
	bool _death_flag = false;

	//! count
	float _lerp_count       = 0.f;
	int _damage_count       = 0;
	double _animation_count = 0;
	int _shot_pending_count = 0;
	int _respawn_time       = 0;

	//! material
	Material _model_material;
};
