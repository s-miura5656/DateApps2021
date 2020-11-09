#include "../../ESGLib.h"
#include "../Enum/Enum.h"

class PlayerBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

	virtual bool Initialize() { return true; }
	virtual int Update() { return 0; }
	virtual void Draw2D();
	virtual void Draw3D();

	OrientedBoundingBox PlayerGetObb() { return player_obb; }
	
	Vector3 PlayerGetPos() { return player->GetPosition(); }

	MODEL GetPlayer() { return player; }

protected:
	MODEL player;
	MODEL rocket_punch;

	float scale;
	float angle;
	
	SimpleShape shape;

	MODEL player_hitbox;
	OrientedBoundingBox player_obb;
	
	GamePadState  pad_state;
	GamePadBuffer pad_buffer;
};
