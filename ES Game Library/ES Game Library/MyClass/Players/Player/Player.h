//! @file   Player.h
//! @brief  �v���C���[�̓������N���X
//! @author Souta_Miura
//! @date   2020/11/06

#pragma once

#include "../PlayerBase.h"

class Player : public PlayerBase
{
public:
	Player (std::string name);
	~Player () override;

	bool Initialize() override;

private:
};