#pragma once

#include "../../ESGLib.h"
#include <sstream>

//! @fn 文字列から数字を取り出す関数
//! @brief 文字列の _ があるところの後の数字を抜き出す 
//! @detail name_1 だと 1 の部分がint型として取り出される
static int GetTagNum(std::string tag)
{
	int num = tag.find("_");

	tag.erase(0, num + 1);

	std::istringstream(tag) >> num;

	return num;
}

//! @fn 値を指定された範囲に収める関数
//! @param (value) 範囲内に収める値
//! @param (min) 収める値の下限値 
//! @param (max) 収める値の上限値
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

//! @fn ベクトルの線形補完
//! @param (A) 始点
//! @param (B) 終点
//! @@aram (t) 割合(0~1の間)
static Vector3 Vector3_Lerp(Vector3 A, Vector3 B, float t)
{
	Vector3 Lerp = Vector3_Zero;

	Lerp.x = MathHelper_Lerp(A.x, B.x, t);
	Lerp.y = MathHelper_Lerp(A.y, B.y, t);
	Lerp.z = MathHelper_Lerp(A.z, B.z, t);

	return Lerp;
}


//! @fn  壁ずりベクトルの作成
//! @param (model) 壁ずりさせたいモデル
//! @param (pos) 壁ずりさせたいモデルの座標
//! @param (dir) 壁ずりさせたいモデルのベクトル
//! @return 壁ずりベクトル
Vector3 SlidingOnWallCreation(MODEL model, Vector3 pos, Vector3 dir)
{
	Vector3 _normal;

	model->IntersectRay(pos, dir, nullptr, &_normal);

	return dir + Vector3_Dot(-dir, _normal) * _normal;
}