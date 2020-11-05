//! @file   PlayerManager.h
//! @brief  プレイヤー用の管理クラス
//! @author Souta_Miura
//! @date   2020/11/05
#pragma once

#include "../ManagerBase.h"

class PlayerBase;

class PlayerManager : public ManagerBase
{
public:
	PlayerManager();
	~PlayerManager();

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;

private:
	//プレイヤー
	std::vector<PlayerBase*> players;
	int const player_max_count = 4;
};
