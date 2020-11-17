#pragma once

#include "../../ESGLib.h"
#include <sstream>

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
	float ratio = max - min;

	ratio /= 100.f;

	value *= ratio;

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
Vector3 SlidingOnWallCreation(MODEL model, Vector3 pos, Vector3 dir)
{
	Vector3 _normal;

	model->IntersectRay(pos, dir, nullptr, &_normal);

	return dir + Vector3_Dot(-dir, _normal) * _normal;
}