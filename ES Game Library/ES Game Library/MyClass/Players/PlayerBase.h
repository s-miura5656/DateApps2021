#include "../../ESGLib.h"
#include "Arm/Arm.h"
#include "../Collision/HitBox.h"
#include "../Data/IData.h"
#include "../Managers/InputManager/InputManager.h"
#include "../Data/StructList.h"
#include"../Managers/AudioManager/AudioManager.h"

class ParticleSystem;
class ArmBase;
class ItemBase;

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

	virtual void GetItem(ItemBase* item,string item_tag);
	virtual void Warp(Vector3 warppos);
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
	void ParameterLevel();
	void InvincibleMode();
	void ItemParameterTime();
	void EffectDraw();

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
	float _warp_time         = 0.f;

	//! position
	Vector3 _old_pos		 = Vector3_Zero;
	Vector3 _new_pos		 = Vector3_Zero;
	Vector3 _warp_other_pos = Vector3_Zero;
	//! pointer
	std::unique_ptr<ArmBase>	                      _arm;
	std::unique_ptr<HitBox>		                      _hit_box;
	std::unique_ptr<IPrayerData>                      _i_player_data;
	std::unique_ptr<IArmData>	                      _i_arm_Data;
	std::unique_ptr<IMapData>                         _i_map_data;
	std::unique_ptr<ParticleSystem>                   _destroy_effect;
	std::unique_ptr<ParticleSystem>                   _smoke_effect;
	std::unique_ptr<ParticleSystem>                   _respawn_effect;
	std::unique_ptr<ParticleSystem>                   _warp_effect;
	std::unique_ptr<ParticleSystem>                   _player_speedup_effect;
	std::unique_ptr<ParticleSystem>                   _arm_speedup_effect;
	std::unique_ptr<ParticleSystem>                   _powerdown_effect;
	std::unique_ptr<ParticleSystem>                   _thunder_effect;
	std::map<string, std::unique_ptr<ParticleSystem>> _effect;
	//! tag
	std::string _tag;
	std::string _arm_tag;
	std::string _status_tag = "";
	std::string _status_old = "";
	//! index
	IndexNum _index_num;
	int _animation_index;

	//! flag 
	bool _move_flag       = false;
	bool _death_flag      = false;
	bool _turn_flag       = false;
	bool _warp_flag       = false;
	bool _move_punch      = false;
	//! count
	float _lerp_count           = 0.f;
	int _damage_hit_count       = 0;
	double _animation_count     = 0;
	int _shot_pending_count     = 0;
	int _respawn_time           = 0;
	int _invincible_count       = 0;
	int _powerup_count          = 0;
	int _powerdown_count        = 9999;
	int _new_point              = 0;
	int _old_point              = 0;
	int _status_time            = 0;
	//! animation_limit
	float _shot_frame = 60.0f;

	//! material
	Material _model_material;

	//! completion_value
	const float _moving_completion_end_value = 1.0f;
};
