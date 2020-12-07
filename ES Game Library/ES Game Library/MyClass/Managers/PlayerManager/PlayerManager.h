//! @file   PlayerManager.h
//! @brief  �v���C���[�p�̊Ǘ��N���X
//! @author Souta_Miura
//! @date   2020/11/05
#pragma once

#include "../ManagerBase.h"
#include "../../Data/IData.h"

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

	void RankingSort();

private:
	//�v���C���[
	std::vector<Player*> players;
	IPrayerData*		 i_player_data;
	IArmData*			 i_arm_data;
};
