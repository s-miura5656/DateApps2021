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

	bool FileInitialize(LPCTSTR& file);
	bool Initialize() override;
	int Update() override;
	void Move();

	void PlayerColor(Material& mat) {
		player->SetMaterial(mat);
		//rocket_punch->SetMaterial(mat);
	}

	void PlayerStartPosition(Vector3& pos) { player->SetPosition(pos); }

private:
	Vector3 player_get_pos;
	Vector3 player_get_rot;

};