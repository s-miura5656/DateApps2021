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
	
	void ChangePlayerSpeed();

protected:
	MODEL player;

	const float scale = 0.004f;
	const float player_scale = 1.f;
	float angle = 0.f;
	float _move_speed;
	float _weight;

	ArmBase* arm;
	IPrayerData* _iplayer_data;
	std::unique_ptr<HitBox> _hit_box;
	std::string _tag;
};
