//! @file   PlayerManager.h
//! @brief  �v���C���[�p�̊Ǘ��N���X
//! @author Souta_Miura
//! @date   2020/11/05
#pragma once

#include "../ManagerBase.h"
#include "../../Data/IData.h"
#include "../../Players/Crown/CrownRotation.h"

class Player;
class CrownRotation;

using namespace std;

class PlayerManager : public ManagerBase
{
public:
	PlayerManager();
	~PlayerManager() override;

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override;

	void RankingSort();

private:
	//�v���C���[
	std::vector<std::unique_ptr<Player>>     _players;
	std::unique_ptr<IPrayerData>		     _i_player_data;
	std::unique_ptr<IArmData>			     _i_arm_data;
	std::unique_ptr<CrownRotation>			 _crown_rotation;
	std::string name[PLAYER_COUNT_MAX];
};
