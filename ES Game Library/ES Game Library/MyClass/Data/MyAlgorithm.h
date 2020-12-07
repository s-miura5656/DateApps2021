#pragma once

#include "../../ESGLib.h"
#include <sstream>
#include <codecvt>

//! @fn �����񂩂琔�������o���֐�
//! @brief ������� _ ������Ƃ���̌�̐����𔲂��o�� 
//! @detail name_1 ���� 1 �̕�����int�^�Ƃ��Ď��o�����
static int GetTagNum(std::string tag)
{
	int num = tag.find("_");

	tag.erase(0, num + 1);

	std::istringstream(tag) >> num;

	return num;
}

//! @fn �l���w�肳�ꂽ�͈͂Ɏ��߂�֐�
//! @param (value) �͈͓��Ɏ��߂�l
//! @param (min) ���߂�l�̉����l 
//! @param (max) ���߂�l�̏���l
static float Clamp(float value, float min, float max)
{
	if (value < min)
		value = min;

	if (value > max)
		value = max;

	return value;
}

//! @fn �x�N�g���̐��`�⊮
//! @param (A) �n�_
//! @param (B) �I�_
//! @@aram (t) ����(0~1�̊�)
static Vector3 Vector3_Lerp(Vector3 A, Vector3 B, float t)
{
	Vector3 Lerp = Vector3_Zero;

	Lerp.x = MathHelper_Lerp(A.x, B.x, t);
	Lerp.y = MathHelper_Lerp(A.y, B.y, t);
	Lerp.z = MathHelper_Lerp(A.z, B.z, t);

	return Lerp;
}


//! @fn  �ǂ���x�N�g���̍쐬
//! @param (model) �ǂ��肳���������f��
//! @param (pos) �ǂ��肳���������f���̍��W
//! @param (dir) �ǂ��肳���������f���̃x�N�g��
//! @return �ǂ���x�N�g��
static Vector3 SlidingOnWallVectorCreate(MODEL model, Vector3 pos, Vector3 move_dir)
{
	Vector3 _normal = Vector3_Zero;

	model->IntersectRay(pos, move_dir, nullptr, &_normal);

	return move_dir + Vector3_Dot(-move_dir, _normal) * _normal;
}

//! @fn  �p�x�̌v�Z
//! @param (pad_x) �p�b�h���͂� X
//! @param (pad_y) �p�b�h���͂� Y
//! @return Y���̊p�x
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

//! @fn  �O�����̎擾
//! @brief ��]������O�����̎擾
//! @param (angle) �I�C���[�̉�]��
//! @return �O����
static Vector3 DirectionFromAngle(Vector3 angle) 
{
	auto matrix_x = Matrix_CreateRotationX(angle.x);

	auto matrix_y = Matrix_CreateRotationY(angle.y);

	auto matrix_z = Matrix_CreateRotationZ(angle.z);

	Matrix front_matrix = matrix_x * matrix_y * matrix_z;

	return Vector3_Normalize(Vector3((int)front_matrix._31, (int)front_matrix._32, (int)front_matrix._33));
}

//! @fn  Path�ϊ�
//! @brief �}���`�o�C�g����������j�R�[�h������ɕϊ����ăp�X�ɂ���
//! @param (path) �t�@�C���̂���p�X
//! @param (name) �t�@�C���̖��O (�g���q�͊܂܂Ȃ�)
//! @param (extension) �t�@�C���̊g���q (.png��.X��)
//! @return �O����
static std::wstring ConvertFilePath(string path, string name, string extension)
{
	std::wstring file_path = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(path);

	std::wstring file_name = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(name);

	std::wstring file_extension = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(extension);

	return file_path = file_path + file_name + file_extension;
}