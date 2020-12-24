//! @file   StageBase.h
//! @brief  ステージ用の管理クラス
//! @author Souta_Miura
//! @date   2020/11/09
#pragma once

#include"../../Managers/ManagerBase.h"
#include"../../Stage/Stage_1/Block/Block.h"
#include"../../Stage/Stage_1/Indestructible/Indestructible.h"
#include"../../Stage/Stage_1/RotatingFloor/RotatingFloor .h"
#include"../../Stage/Stage_1/Warp/Warp.h"
class StageBase;
class HitBox;


class StageManager : public ManagerBase
{
public:
	StageManager();
	~StageManager();

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override;

private:
	bool RandomBlockSet();
	std::vector<StageBase*>		stages;
	std::vector<cstring>		mapdate; //! マップデータの読み込み
	SPRITE _bg_sprite;
	int _count = 0;
	int _map_width_count = 0;
	int _map_depth_count = 0;
	int time = 0;
	Vector3 _map_start_positoin;
	std::vector<Vector3> _metal_position;
};