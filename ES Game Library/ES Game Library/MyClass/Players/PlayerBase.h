#include "../../ESGLib.h"
#include "Arm/Arm.h"
#include "../Collision/HitBox.h"
#include "../Data/IPlayerData.h"

class PlayerBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

	virtual bool Initialize() { return true; }
	virtual int Update() { return 0; }
	virtual void Draw2D();
	virtual void Draw3D();

	Vector3 GetPos() { return player->GetPosition(); }
	float GetAngle() { return angle; }
	MODEL GetPlayer() { return player; }
	
	float PlayerSpeed();

protected:
	MODEL player;

	const float scale = 0.004f;
	const float player_scale = 1.f;
	float angle   = 0.f;
	float _speed  = 0.f;
	float _weight = 0.f;
	float _move_speed = 0.f;

	ArmBase* arm;
	IPrayerData* _iplayer_data;
	IArmData* _iarm_data;
	std::unique_ptr<HitBox> _hit_box;
	std::string _tag;
	std::string _arm_tag;
};
