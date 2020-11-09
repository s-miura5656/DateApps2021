//! @file   CollisionBase.h
//! @brief  当たり判定用の基底クラス
//! @author Souta_Miura
//! @date   2020/11/05
#pragma once

#include "../../ESGLib.h"

class CollisionBase
{
public:
	CollisionBase();
	virtual ~CollisionBase();

	virtual bool Initialize();
	virtual void Draw3D();

protected:
	MODEL box;
	OrientedBoundingBox hit_box;
};
