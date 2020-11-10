//! @file   CollisionBase.h
//! @brief  �����蔻��p�̊��N���X
//! @author Souta_Miura
//! @date   2020/11/05

#include "../Collision/CollisionBase.h"

CollisionBase::CollisionBase()
{
	
}

CollisionBase::~CollisionBase()
{

}

bool CollisionBase::Initialize()
{
	return true;
}


void CollisionBase::Draw3D()
{
#ifdef DEBUG
	GraphicsDevice.BeginAlphaBlend();
	box->DrawAlpha(0.5f);
	GraphicsDevice.EndAlphaBlend();
#endif
}