#pragma once

#include "../../../ESGLib.h"
#include "../../Data/IData.h"

struct PointMove
{
	Vector3 position;
	float theta;
	int point;
	float alpha;
	PointMove()
	{
		position = Vector3_Zero;
		theta = 0.0f;
		point = 0;
		alpha = 0;
	}
};

class PointAnimation
{
public:
	PointAnimation();
	~PointAnimation();

	void RegisterPointAnimation(Vector3 player_pos, std::string tag, int prev_rank_point);
	void MovePointAnimation(Vector3 player_pos);

private:

	std::vector<PointMove> pointMove;
	std::vector<Vector3> move_pos;

	IPrayerData* _i_player_data;

};

