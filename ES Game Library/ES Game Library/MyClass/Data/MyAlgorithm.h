#pragma once

#include "../../ESGLib.h"
#include <sstream>
#include <codecvt>

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
static Vector3 SlidingOnWallVectorCreate(MODEL model, Vector3 pos, Vector3 move_dir)
{
	Vector3 _normal = Vector3_Zero;

	model->IntersectRay(pos, move_dir, nullptr, &_normal);

	return move_dir + Vector3_Dot(-move_dir, _normal) * _normal;
}

//! @fn  角度の計算
//! @param (pad_x) パッド入力の X
//! @param (pad_y) パッド入力の Y
//! @return Y軸の角度
static float AngleCalculating(float pad_x, float pad_y)
{
	auto a = double(pad_x - Axis_Center) / double(Axis_Max);

	auto b = -double(pad_y - Axis_Center) / double(Axis_Max);

	float angle = MathHelper_Atan2(a, b);

	return angle;
}

static Vector3 MoveDirection(float pad_x, float pad_y)
{
	auto x = Clamp(pad_x, -0.1f, 0.1f);

	auto z = -Clamp(pad_y, -0.1f, 0.1f);

	auto pos = Vector3(x, 0, z);

	return Vector3_Normalize(pos);
}

static int AngleClamp(float angle)
{
	int _angle = angle;

	if (_angle <= 0)
	{
		_angle += 360;
	}

	if (_angle >= 360 - 45 || _angle < 0 + 45)
	{
		_angle = 0;
	}
	else if (_angle >= 90 - 45 && _angle < 90 + 45)
	{
		_angle = 90;

	}
	else if (_angle >= 180 - 45 && _angle < 180 + 45)
	{
		_angle = 180;
	}
	else if (_angle >= 270 - 45 && _angle < 270 + 45)
	{
		_angle = 270;
	}

	return _angle;
}

//! @fn  前方向の取得
//! @brief 回転軸から前方向の取得
//! @param (angle) オイラーの回転軸
//! @return 前方向
static Vector3 DirectionFromAngle(Vector3 angle) 
{
	auto matrix_x = Matrix_CreateRotationX(angle.x);

	auto matrix_y = Matrix_CreateRotationY(angle.y);

	auto matrix_z = Matrix_CreateRotationZ(angle.z);

	Matrix front_matrix = matrix_x * matrix_y * matrix_z;

	return Vector3_Normalize(Vector3((int)front_matrix._31, (int)front_matrix._32, (int)front_matrix._33));
}

//! @fn  Path変換
//! @brief マルチバイト文字列をユニコード文字列に変換してパスにする
//! @param (path) ファイルのあるパス
//! @param (name) ファイルの名前 (拡張子は含まない)
//! @param (extension) ファイルの拡張子 (.pngや.X等)
//! @return 前方向
static std::wstring ConvertFilePath(string path, string name, string extension)
{
	std::wstring file_path = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(path);

	std::wstring file_name = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(name);

	std::wstring file_extension = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(extension);

	return file_path = file_path + file_name + file_extension;
}