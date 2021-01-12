#include "PlayerSpeedUp.h"

bool PlayerSpeedUp::Initialize(int time)
{
	_effect_time  = time;
	_player_speed = 0.09;
	_arm_speed    = 0.1;
	return false;
}

int PlayerSpeedUp::Updata()
{
	return 0;
}