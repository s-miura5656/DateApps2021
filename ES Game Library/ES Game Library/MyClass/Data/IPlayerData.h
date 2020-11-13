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
	void SetAngle(std::string& player_name, float angle) { PlayerParametor::Instance()._player_params[player_name].angle = angle; }
	

	//! ゲッター
	PlayerParam GetPlayerPram(std::string& player_name) { return PlayerParametor::Instance()._player_params[player_name]; }
	int GetHitPoint(std::string& player_name) { return PlayerParametor::Instance()._player_params[player_name].hit_point; }
	int GetAttackPowor(std::string& player_name) { return PlayerParametor::Instance()._player_params[player_name].attack_powor; }
	int GetSpeed(std::string& player_name) { return PlayerParametor::Instance()._player_params[player_name].speed; }
	int GetWeight(std::string& player_name) { return PlayerParametor::Instance()._player_params[player_name].weight; }
	float GetAngle(std::string& player_name) { return PlayerParametor::Instance()._player_params[player_name].angle; }
	Vector3 GetPosition(std::string& player_name) { return PlayerParametor::Instance()._player_params[player_name].position; }
	
private:
};

class IArmData 
{
public:
	IArmData() {};
	~IArmData() {};

	//! セッター
	void SetArmParam(std::string& arm_name, ArmParam& arm_param) { ArmParametor::Instance()._arm_params[arm_name] = arm_param; }
	void SetAttackPowor(std::string& arm_name, int attack_powor) { ArmParametor::Instance()._arm_params[arm_name].attack_powor = attack_powor; }
	void SetWeight(std::string& arm_name, int weight) { ArmParametor::Instance()._arm_params[arm_name].weight = weight; }
	void SetPosition(std::string& arm_name, Vector3 pos) { ArmParametor::Instance()._arm_params[arm_name].position = pos; }
	void SetAngle(std::string& arm_name, float angle) { ArmParametor::Instance()._arm_params[arm_name].angle = angle; }
	void SetTurns(std::string& arm_name, int turns) { ArmParametor::Instance()._arm_params[arm_name].tunns = turns; }

	//! ゲッター
	ArmParam GetPlayerPram(std::string& arm_name) { return ArmParametor::Instance()._arm_params[arm_name]; }
	int GetAttackPowor(std::string& arm_name) { return ArmParametor::Instance()._arm_params[arm_name].attack_powor; }
	int GetWeight(std::string& arm_name) { return ArmParametor::Instance()._arm_params[arm_name].weight; }
	int GetTurns(std::string& arm_name) { return ArmParametor::Instance()._arm_params[arm_name].tunns; }
	float GetAngle(std::string& arm_name) { return ArmParametor::Instance()._arm_params[arm_name].angle; }
	Vector3 GetPosition(std::string& arm_name) { return ArmParametor::Instance()._arm_params[arm_name].position; }
};