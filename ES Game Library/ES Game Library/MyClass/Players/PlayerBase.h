#include "../../ESGLib.h"
//#include "../Enum/Enum.h"
#include "Arm/Arm.h"

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

protected:
	MODEL player;

	const float scale = 0.004f;
	const float player_scale = 1.f;
	float angle;

	SimpleShape shape;

	MODEL player_hitbox;
	ArmBase* arm;
};
