//! @file   StageBase.h
//! @brief  ステージ用の管理クラス
//! @author Souta_Miura
//! @date   2020/11/09
#pragma once

#include"../ManagerBase.h"
#include"../../Stage/Block/Block.h"
#include"../../Stage/Pillar/Pillar.h"
#include"../../Stage/Metal/Metal.h"
#include"../../Stage/Floor/Floor.h"
class StageBase;

class StageManager : public ManagerBase
{
public:
	StageManager();
	~StageManager();

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;

private:
	Block* block;//!破壊できるブロックのクラス
	Pillar* pillar;//!破壊できないブロックのクラス
	Metal* metal;//!外壁のクラス
	Floor*floor;//!床のクラス
	std::vector<cstring> mapdate;//!マップデータの読み込み
};