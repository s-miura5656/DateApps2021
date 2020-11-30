//! @file   Player.h
//! @brief  プレイヤーの動かすクラス
//! @author Souta_Miura
//! @date   2020/11/06

#pragma once

#include "../PlayerBase.h"

class Player : public PlayerBase
{
public:
	Player (std::string name);
	~Player ();

	bool Initialize() override;
	int Update() override;

	void PlayerStartPosition(Vector3& pos) { _model->SetPosition(pos); }
	void DebugControll();
private:
};