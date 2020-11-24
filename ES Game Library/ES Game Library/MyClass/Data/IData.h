//! @file   Parametor.h
//! @brief  各キャラクターのパラメーターインターフェース
//! @author Souta_Miura
//! @date   2020/11/06

#pragma once

#include "Parametor.h"
#include "StructList.h"

class IPrayerData
{
public:
	IPrayerData() {};
	~IPrayerData() {};

	//! セッター
	void SetPlayerParam(std::string& player_tag, PlayerParam& player_param) { PlayerParametor::Instance()._player_params[player_tag] = player_param; }
	void SetHitPoint(std::string& player_tag, int hit_point)				{ PlayerParametor::Instance()._player_params[player_tag].hit_point = hit_point; }
	void SetAttackPowor(std::string& player_tag, int attack_powor)			{ PlayerParametor::Instance()._player_params[player_tag].attack_powor = attack_powor; }
	void SetSpeed(std::string& player_tag, int speed)						{ PlayerParametor::Instance()._player_params[player_tag].speed = speed; }
	void SetWeight(std::string& player_tag, int weight)						{ PlayerParametor::Instance()._player_params[player_tag].weight = weight; }
	void SetAngle(std::string& player_tag, float angle)						{ PlayerParametor::Instance()._player_params[player_tag].angle = angle; }
	void SetPosition(std::string& player_tag, Vector3 pos)					{ PlayerParametor::Instance()._player_params[player_tag].position = pos; }
	void SetState(std::string& player_tag, int state)						{ PlayerParametor::Instance()._player_params[player_tag].state = state; }

	//! ゲッター
	PlayerParam GetPlayerPram(std::string& player_tag)  const { return PlayerParametor::Instance()._player_params[player_tag]; }
	int GetHitPoint(std::string& player_tag)			const { return PlayerParametor::Instance()._player_params[player_tag].hit_point; }
	int GetAttackPowor(std::string& player_tag)			const { return PlayerParametor::Instance()._player_params[player_tag].attack_powor; }
	int GetSpeed(std::string& player_tag)				const { return PlayerParametor::Instance()._player_params[player_tag].speed; }
	int GetWeight(std::string& player_tag)				const { return PlayerParametor::Instance()._player_params[player_tag].weight; }
	float GetAngle(std::string& player_tag)				const { return PlayerParametor::Instance()._player_params[player_tag].angle; }
	Vector3 GetPosition(std::string& player_tag)		const { return PlayerParametor::Instance()._player_params[player_tag].position; }
	int GetState(std::string& player_tag)				const { return PlayerParametor::Instance()._player_params[player_tag].state; }
	
private:
};

class IArmData 
{
public:
	IArmData() {};
	~IArmData() {};

	//! セッター
	void SetArmParam(std::string& arm_tag, ArmParam& arm_param)  { ArmParametor::Instance()._arm_params[arm_tag] = arm_param; }
	void SetAttackPowor(std::string& arm_tag, int attack_powor)  { ArmParametor::Instance()._arm_params[arm_tag].attack_powor = attack_powor; }
	void SetWeight(std::string& arm_tag, int weight)			 { ArmParametor::Instance()._arm_params[arm_tag].weight = weight; }
	void SetPosition(std::string& arm_tag, Vector3 pos)			 { ArmParametor::Instance()._arm_params[arm_tag].position = pos; }
	void SetAngle(std::string& arm_tag, float angle)			 { ArmParametor::Instance()._arm_params[arm_tag].angle = angle; }
	void SetTurns(std::string& arm_tag, int turns)				 { ArmParametor::Instance()._arm_params[arm_tag].tunns = turns; }

	//! ゲッター
	ArmParam GetPlayerPram(std::string& arm_tag)  const { return ArmParametor::Instance()._arm_params[arm_tag]; }
	int GetAttackPowor(std::string& arm_tag)	  const { return ArmParametor::Instance()._arm_params[arm_tag].attack_powor; }
	int GetWeight(std::string& arm_tag)			  const { return ArmParametor::Instance()._arm_params[arm_tag].weight; }
	int GetTurns(std::string& arm_tag)			  const { return ArmParametor::Instance()._arm_params[arm_tag].tunns; }
	float GetAngle(std::string& arm_tag)		  const { return ArmParametor::Instance()._arm_params[arm_tag].angle; }
	Vector3 GetPosition(std::string& arm_tag)	  const { return ArmParametor::Instance()._arm_params[arm_tag].position; }
};

class IMapData {
public:
	IMapData() {};
	~IMapData() {};
	void SetPosition(Vector3 pos) { MapPosition::Instance()._position.push_back(pos); }
	std::vector<Vector3> GetPosition() const { return MapPosition::Instance()._position; }
};