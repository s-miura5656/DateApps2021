//! @file   CollisionBase.h
//! @brief  �����蔻��p�̊��N���X
//! @author Souta_Miura
//! @date   2020/11/05
#pragma once

#include "../../ESGLib.h"

class CollisionBase
{
public:
	CollisionBase();
	virtual ~CollisionBase();

	virtual void Initialize();
	virtual void Draw3D();

protected:
	MODEL box;
	OrientedBoundingBox hit_box;
};
