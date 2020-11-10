#include "RocketPunchBase.h"


class RocketPunch :public RocketPunchBase
{
public:
	RocketPunch();
	~RocketPunch();

	bool Fileinitialize(LPCTSTR& file);
	bool Initialize()override;
	int  Update()override;

	void PlayerColor(Material& mat) {
		rocket_punch->SetMaterial(mat);
	}

protected:
	
	Vector3 punch_get_pos;
	Vector3 punch_get_rot;

	int   punch_state;
	float move_speed;
	float punch_speed;
	
};
