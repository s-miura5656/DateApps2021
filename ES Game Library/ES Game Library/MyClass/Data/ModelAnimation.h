#pragma once

#include "../../ESGLib.h"
#include <sstream>

static void ModelRotation(Vector3 rotation, MODEL model)
{
	model->Rotation(rotation.x, rotation.y, rotation.z);
}

//! @fn モデルを点滅させる関数
//! @param (alpha_max) 透明度の上限値
//! @param (alpha_min) 透明度の下限値
//! @param (set_alpha) 透明度の初期値
//! @param (speed) 点滅の速さ
//! @param (model) 点滅させたいモデル
//! @return 透明度の初期値をfloat型で返す
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

//! @fn モデルを拡大縮小する関数
//! @param (scale_max) 拡大の最大値
//! @param (scale_min) 縮小の最大値
//! @param (scale_set) モデルの大きさの初期値
//! @param (speed) 拡縮の速さ
//! @param (model) 拡縮させるモデル
//! @return モデルの大きさの初期値をfloat型で返す
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

//! @fn モデルを跳ねさせる関数
//! @param (bound_max) 
//! @param (speed) 跳ねる速さ
//! @param (model) 跳ねさせるモデル
static void ModelBound(Vector3 bound_max, float speed, MODEL model)
{
	static float theta = 0.0f;

	Vector3 pos = model->GetPosition();

	pos.x = MathHelper_Sin(theta) * bound_max.x;
	pos.y = MathHelper_Sin(theta) * bound_max.y;
	pos.z = MathHelper_Sin(theta) * bound_max.z;
	model->SetPosition(pos);

	theta += speed;
	if (theta >= 360.0f)
		theta -= 360.0f;
}