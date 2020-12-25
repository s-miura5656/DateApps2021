#include "../../ESGLib.h"
#include "Arm/Arm.h"
#include "../Collision/HitBox.h"
#include "../Data/IData.h"
#include "../Managers/InputManager/InputManager.h"
#include "../Data/StructList.h"

class ParticleSystem;

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
	void ChangeAnimation();
	void CreateArm();
	void DestroyArm();
	void InputMove(BaseInput* pad);
	void Move();
	void InputMoveDirection(BaseInput* pad);
	void InputAngle(BaseInput* pad);
	void SetCollisionPosition();
	void DebugControll();

	//! file
	ANIMATIONMODEL		_model;
	FONT				_font;
	EFFECT				_shader;
	SPRITE				_texture;

	//! transform
	Transform _transform;

	float _angle			 = 0.f;
	float _old_angle		 = 0.f;
	float _speed			 = 0.f;
	float _move_speed		 = 0.f;
	float _distance			 = FLT_MAX;

	//! position
	Vector3 _old_pos		 = Vector3_Zero;
	Vector3 _new_pos		 = Vector3_Zero;

	//! pointer
	std::unique_ptr<ArmBase>	    _arm;
	std::unique_ptr<HitBox>		    _hit_box;
	std::unique_ptr<IPrayerData>    _i_player_data;
	std::unique_ptr<IArmData>	    _i_arm_Data;
	std::unique_ptr<IMapData>       _i_map_data;
	std::unique_ptr<ParticleSystem> _destroy_effect;

	//! tag
	std::string _tag;
	std::string _arm_tag;

	//! index
	IndexNum _index_num;
	int _animation_index;

	//! flag 
	bool _move_flag  = false;
	bool _death_flag = false;
	bool _turn_flag  = false;

	//! count
	float _lerp_count       = 0.f;
	int _damage_hit_count   = 0;
	double _animation_count = 0;
	int _shot_pending_count = 0;
	int _respawn_time       = 0;

	//! animation_limit
	float _shot_frame = 60.0f;

	//! material
	Material _model_material;

	//! completion_value
	const float _moving_completion_end_value = 1.0f;
};
