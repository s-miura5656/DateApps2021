#include "../../ESGLib.h"
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

	//OrientedBoundingBox PlayerGetObb() { return player_obb; }
	
	Vector3 GetPos() { return player->GetPosition(); }
	float GetAngle() { return angle; }
	//Vector3 GetArmPos() { return rocket_punch->GetPosition(); }
	MODEL GetPlayer() { return player; }

protected:
	MODEL player;
	//MODEL rocket_punch;

	const float scale = 0.004f;
	const float player_scale = 1.f;
	float angle;

	SimpleShape shape;

	MODEL player_hitbox;
	//OrientedBoundingBox player_obb;

	/*GamePadState  pad_state;
	GamePadBuffer pad_buffer;*/

	ArmBase* arm;
};
