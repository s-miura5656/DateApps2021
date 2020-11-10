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
	MODEL _box;
	OrientedBoundingBox _hit_box;
	bool _attack_hit = false;
};
