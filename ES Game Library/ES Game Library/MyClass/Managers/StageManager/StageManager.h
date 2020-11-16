//! @file   StageBase.h
//! @brief  ステージ用の管理クラス
//! @author Souta_Miura
//! @date   2020/11/09
#pragma once

#include"../../Managers/ManagerBase.h"
#include"../../Stage/Stage_1/Block/Block.h"
#include"../../Stage/Stage_1/Pillar/Pillar.h"
#include"../../Stage/Stage_1/Metal/Metal.h"
#include"../../Stage/Stage_1/Floor/Floor.h"
#include "../../Data/GameData.h"
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
	std::map<std::string, StageBase*> stages;
	std::vector<cstring> mapdate;//!マップデータの読み込み
};