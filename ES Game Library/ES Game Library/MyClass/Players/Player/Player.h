//! @file   Player.h
//! @brief  プレイヤーの動かすクラス
//! @author Souta_Miura
//! @date   2020/11/06

#pragma once

#include "../PlayerBase.h"

class Player : public PlayerBase
{
public:
	Player ();
	~Player ();

	
	bool Initialize() override;
	int Update() override;

private:

};