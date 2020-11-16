#pragma once

#include "../../ESGLib.h"
#include <sstream>

static int GetTagNum(std::string tag)
{
	int num = tag.find("_");

	tag.erase(0, num + 1);

	std::istringstream(tag) >> num;

	return num;
}

static float Clamp(float value, float min, float max)
{
	float ratio = max - min;

	ratio /= 100.f;

	value *= ratio;

	if (value < min)
		value = min;

	if (value > max)
		value = max;

	return value;
}

static Vector3 Vector3_Lerp(Vector3 A, Vector3 B, float t)
{
	Vector3 Lerp = Vector3_Zero;

	Lerp.x = MathHelper_Lerp(A.x, B.x, t);
	Lerp.y = MathHelper_Lerp(A.y, B.y, t);
	Lerp.z = MathHelper_Lerp(A.z, B.z, t);

	return Lerp;
}