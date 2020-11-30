#pragma once

#include "../../../../ESGLib.h"
#include <sstream>

static void ModelRotation(Vector3 rotation, MODEL model)
{

	model->Rotation(rotation.x, rotation.y, rotation.z);

}

static float ModelFlashing(float alpha_max, float alpha_min, float set_alpha, float speed, MODEL model)
{

	
	static bool alpha_flag = true;

	if (alpha_flag)
	{
		set_alpha += speed;
		if (set_alpha >= alpha_max)
		{
			alpha_flag = !alpha_flag;
		}
	}
	else
	{
		set_alpha -= speed;
		if (set_alpha <= alpha_min)
		{
			alpha_flag = !alpha_flag;
		}
	}

	return set_alpha;
	
	
}
	 
static float ModelScaling(float scale_max, float scale_min, float set_scale, float speed, MODEL model)
{
	static bool scale_flag = false;

	if (scale_flag)
	{
		set_scale += speed;
		if(set_scale >= scale_max)
		{ 
			scale_flag = !scale_flag;
		}
	}
	else
	{
		set_scale -= speed;
		if(set_scale <= scale_min)
		{
			scale_flag = !scale_flag;
		}
	}

	
	return set_scale;
}

static float ModelBound(float bound_x_max, float bound_y_max, float bound_z_max, float speed, MODEL model)
{
	static float theta = 0.0f;

	Vector3 pos = model->GetPosition();
	pos.x = MathHelper_Sin(theta) * bound_x_max;
	pos.y = MathHelper_Sin(theta) * bound_y_max;
	pos.z = MathHelper_Sin(theta) * bound_z_max;
	model->SetPosition(pos);

	theta += speed;
	if (theta >= 360.0f)
		theta -= 360.0f;

	return bound_x_max, bound_y_max, bound_z_max;
}

static float ModelImpact()
{
	// ÕŒ‚‚ª‰Á‚í‚Á‚½‚È‚Ç‚ÌAŠÉ‹}‚ª•t‚¢‚½•¨—‰‰Z“I‚È“®‚«



}