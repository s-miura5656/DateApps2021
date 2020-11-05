//! @file   CollisionManager.h
//! @brief  当たり判定用用の管理クラス
//! @author Souta_Miura
//! @date   2020/11/05
#pragma once

#include "../ManagerBase.h"
#include "../../Collision/Collision.h"

class CollisionManager : public ManagerBase
{
public:
	CollisionManager();
	~CollisionManager();

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;

private:

};
