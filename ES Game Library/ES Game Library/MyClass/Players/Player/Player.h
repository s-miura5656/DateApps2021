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

	void PlayerColor(Material& mat) {
		player->SetMaterial(mat);
		rocket_punch->SetMaterial(mat);
	}

	void PlayerStartPosition(Vector3& pos) { player->SetPosition(pos); }
	void SetContorollerNumber(int& pad_num) { pad_number = pad_num; }

private:
	Vector3 player_get_pos;
	Vector3 player_get_rot;

	Vector3 punch_get_pos;
	Vector3 punch_get_rot;

	int  punch_state;
	float move_speed;
	float punch_speed;

	int pad_number;
};