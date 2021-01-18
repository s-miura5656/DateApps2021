#pragma once

#include "../../../ESGLib.h"

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

	void RegisterPointAnimation(Vector3 player_pos);
	void MovePointAnimation(Vector3 player_pos);

private:

};

