#include "RocketPunch.h"

RocketPunch::RocketPunch()
{
}

RocketPunch::~RocketPunch()
{
}

bool RocketPunch::Fileinitialize(LPCTSTR& file)
{
	rocket_punch = GraphicsDevice.CreateModelFromFile(_T("Player/sword_01.X"));
}

bool RocketPunch::Initialize()
{
	punch_state = NO_PUNCH;

	punch_speed = 0.1f;

	rocket_punch->SetScale(0.01f);
}

int RocketPunch::Update()
{
	punch_get_pos = rocket_punch->GetPosition();
	punch_get_rot = rocket_punch->GetRotation();

	float dist = Vector3_Distance(player_get_pos, punch_get_pos);

	if (punch_state == RETURN_PUNCH)
	{
		rocket_punch->Move(0, 0, -punch_speed);
		if (dist <= 0.5) {
			punch_state = NO_PUNCH;
			dist = 0;
		}
	}
	else if (punch_state == PUNCH)
	{
		rocket_punch->Move(0, 0, punch_speed);
		if (dist >= 5)
		{
			dist = 5;
			punch_state = RETURN_PUNCH;
		}
	}
	else if (punch_state == NO_PUNCH)
	{
		rocket_punch->SetPosition(player_get_pos);
	}

}
