//! @file   Player.h
//! @brief  プレイヤーの動かすクラス
//! @author Souta_Miura
//! @date   2020/11/06

#pragma once

#include "../PlayerBase.h"
#include "../../Controller/ContorollerManager.h"

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
	void SetContorollerNumber(int& pad_num) { pad_number = pad_num; }

private:
	Vector3 player_get_pos;
	Vector3 player_get_rot;

	float move_speed;
	
	int   pad_number;

	ControllerManager controller;

};