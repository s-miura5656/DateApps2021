#pragma once

#include "../../ESGLib.h"

struct PlayerParam {
	Vector3 position  = Vector3_Zero;
	int hit_point	  = 1000;
	int attack_powor  = 100;
	int speed		  = 100;
	int weight        = 50;
};