//! @file   PlayerManager.h
//! @brief  �v���C���[�p�̊Ǘ��N���X
//! @author Souta_Miura
//! @date   2020/11/05
#pragma once

#include "../ManagerBase.h"
#include "../../Data/IPlayerData.h"

class Player;

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
	//�v���C���[
	std::vector<Player*> players;
	int const player_max_count = 4;

	IPrayerData* i_player_data;
};