#pragma once

#include "../../ESGLib.h"
#include <sstream>

static void ModelRotation(Vector3 rotation, MODEL model)
{
	model->Rotation(rotation.x, rotation.y, rotation.z);
}

//! @fn ���f����_�ł�����֐�
//! @param (alpha_max) �����x�̏���l
//! @param (alpha_min) �����x�̉����l
//! @param (set_alpha) �����x�̏����l
//! @param (speed) �_�ł̑���
//! @param (model) �_�ł����������f��
//! @return �����x�̏����l��float�^�ŕԂ�
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

//! @fn ���f�����g��k������֐�
//! @param (scale_max) �g��̍ő�l
//! @param (scale_min) �k���̍ő�l
//! @param (scale_set) ���f���̑傫���̏����l
//! @param (speed) �g�k�̑���
//! @param (model) �g�k�����郂�f��
//! @return ���f���̑傫���̏����l��float�^�ŕԂ�
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

//! @fn ���f���𒵂˂�����֐�
//! @param (bound_max) 
//! @param (speed) ���˂鑬��
//! @param (model) ���˂����郂�f��
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