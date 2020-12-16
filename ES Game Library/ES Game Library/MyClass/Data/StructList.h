#pragma once

#include "../../ESGLib.h"
#include "WordsTable.h"

struct PlayerParam {
	int state		  = PlayerEnum::WAIT;
	Vector3 position  = Vector3_Zero;
	float angle		  = 0.f;
	int hit_point	  = 1000;
	int attack_powor  = 1000;
	float speed		  = 0.05f;
	int ranking_point = 0;
	int kill_count    = 0;
	int rank_num      = 0;
};

struct ArmParam {
	int		state					 = ArmEnum::PUNCH;
	Vector3 position				 = Vector3_Zero;
	float   angle					 = 0.f;
	int     attack_powor			 = 200;
	float   go_speed				 = 0.06f;
	float   return_speed			 = 0.3f;
	int     limit_range				 = 20;
	Vector3 hit_position = Vector3_Zero;
	std::vector<Vector3> angle_position;
	std::vector<float> angles;
};

struct MapData {
	Vector3 position = Vector3_Zero;
	bool  move_flag  = false;
};

struct IndexNum {
	int x = 0;
	int y = 0;
	int z = 0;
	void Initialize(int X, int Y, int Z) { x = X; y = Y; z = Z; }
};

struct Transform {
	Vector3 position = Vector3_Zero;
	Vector3 rotation = Vector3_Zero;
	Vector3 scale	 = Vector3_One;
};