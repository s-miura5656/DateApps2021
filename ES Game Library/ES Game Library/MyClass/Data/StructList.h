#pragma once

#include "../../ESGLib.h"

struct PlayerParam {
	Vector3 position  = Vector3_Zero;
	float angle		  = 0.f;
	int hit_point	  = 1000;
	int attack_powor  = 100;
	int speed		  = 100;
	int weight        = 100;
};

struct ArmParam {
	Vector3 position = Vector3_Zero;
	float   angle = 0;
	int     attack_powor = 100;
	int     weight = 50;
	int     tunns = 5;
};