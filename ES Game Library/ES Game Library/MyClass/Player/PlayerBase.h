#include "../../ESGLib.h"
#include "../Enum/Enum.h"

class PlayerBase
{
public:	
	bool FileInitialize(LPCTSTR file);
	virtual bool Initialize(int pad_num, Vector3 pos , Material mat);
	virtual void Update();

	void Draw();

	OrientedBoundingBox PlayerGetObb() { return player_obb; }
	
	Vector3 PlayerGetPos() { return player->GetPosition(); }

	MODEL GetPlayer() { return player; }

protected:
	MODEL player;
	
	MODEL rocket_punch;

	Vector3 player_get_pos;
	Vector3 player_get_rot;

	Vector3 punch_get_pos;
	Vector3 punch_get_rot;

	int  punch_state;

	float scale;
	float angle;
	float move_speed;

	float punch_spped;

	SimpleShape shape;

	MODEL player_hitbox;
	OrientedBoundingBox player_obb;
	
	int pad_number;

	GamePadState  pad_state;
	GamePadBuffer pad_buffer;

};
