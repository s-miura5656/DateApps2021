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
	void RandomBlockSet();
	std::vector<StageBase*>	    _stages;
	std::vector<cstring>		_mapdate; //! マップデータの読み込み
	SPRITE                      _bg_sprite;
	int                         _count;
	int                         _random_fall_time;
	int                         _fall_block_count;
	int                         _block_count;
	float                       _fall_interval;
};