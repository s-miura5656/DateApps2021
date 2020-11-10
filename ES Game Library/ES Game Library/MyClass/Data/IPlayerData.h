//! @file   PlayerParametor.h
//! @brief  プレイヤーのパラメーターのインターフェース
//! @author Souta_Miura
//! @date   2020/11/06

#pragma once

#include "../Players/PlayerParametor/PlayerParametor.h"
#include "StructList.h"

class IPrayerData
{
public:
	IPrayerData() {};
	~IPrayerData() {};

	//! セッター
	void SetPlayerParam(std::string& name, PlayerParam& player_param) { PlayerParametor::Instance()._player_params[name] = player_param; }
	void SetHitPoint(std::string& player_name, int hit_point) { PlayerParametor::Instance()._player_params[player_name].hit_point = hit_point; }
	void SetAttackPowor(std::string& player_name, int attack_powor) { PlayerParametor::Instance()._player_params[player_name].attack_powor = attack_powor; }
	void SetSpeed(std::string& player_name, int speed) { PlayerParametor::Instance()._player_params[player_name].speed = speed; }
	void SetWeight(std::string& player_name, int weight) { PlayerParametor::Instance()._player_params[player_name].weight = weight; }
	void SetPosition(std::string& player_name, Vector3 pos) { PlayerParametor::Instance()._player_params[player_name].position = pos; }
	void SetArmModelPos(std::string& arm_name, Vector3 pos) { PlayerParametor::Instance()._arms_pos[arm_name] = pos; }

	//! ゲッター
	PlayerParam GetPlayerPram(std::string& player_name) { return PlayerParametor::Instance()._player_params[player_name]; }
	int GetHitPoint(std::string& player_name) { return PlayerParametor::Instance()._player_params[player_name].hit_point; }
	int GetAttackPowor(std::string& player_name) { return PlayerParametor::Instance()._player_params[player_name].attack_powor; }
	int GetSpeed(std::string& player_name) { return PlayerParametor::Instance()._player_params[player_name].speed; }
	int GetWeight(std::string& player_name) { return PlayerParametor::Instance()._player_params[player_name].weight; }
	Vector3 GetPosition(std::string& player_name) { return PlayerParametor::Instance()._player_params[player_name].position; }
	Vector3 GetArmModelPos(std::string& arm_name) { return PlayerParametor::Instance()._arms_pos[arm_name]; }
private:
};