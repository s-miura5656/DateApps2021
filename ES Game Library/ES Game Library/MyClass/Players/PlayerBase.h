#include "../../ESGLib.h"
#include "../Enum/Enum.h"

class PlayerBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

	void PlayerColor(Material& mat) {
		player->SetMaterial(mat);
		rocket_punch->SetMaterial(mat);
	}

	void PlayerStartPosition(Vector3& pos) { player->SetPosition(pos); }
	void SetContorollerNumber(int& pad_num) { pad_number = pad_num; }
	bool FileInitialize(LPCTSTR& file);
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

	Vector3 player_get_pos;
	Vector3 player_get_rot;

	Vector3 punch_get_pos;
	Vector3 punch_get_rot;

	int  punch_state;

	float scale;
	float angle;
	float move_speed;

	float punch_speed;

	SimpleShape shape;

	MODEL player_hitbox;
	OrientedBoundingBox player_obb;
	
	int pad_number;

	GamePadState  pad_state;
	GamePadBuffer pad_buffer;

};
