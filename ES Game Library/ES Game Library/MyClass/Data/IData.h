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
	void SetParametor(std::string& player_tag, PlayerParam& player_param)   { PlayerParametor::Instance()._player_params[player_tag] = player_param; }
	void SetHitPoint(std::string& player_tag, int hit_point)				{ PlayerParametor::Instance()._player_params[player_tag].hit_point = hit_point; }
	void SetAttackPowor(std::string& player_tag, int attack_powor)			{ PlayerParametor::Instance()._player_params[player_tag].attack_powor = attack_powor; }
	void SetSpeed(std::string& player_tag, float speed)						{ PlayerParametor::Instance()._player_params[player_tag].speed = speed; }
	void SetRankingPoint(std::string& player_tag, int ranking_point)		{ PlayerParametor::Instance()._player_params[player_tag].ranking_point = ranking_point; }
	void SetAngle(std::string& player_tag, float angle)						{ PlayerParametor::Instance()._player_params[player_tag].angle = angle; }
	void SetPosition(std::string& player_tag, Vector3 pos)					{ PlayerParametor::Instance()._player_params[player_tag].position = pos; }
	void SetState(std::string& player_tag, int state)						{ PlayerParametor::Instance()._player_params[player_tag].state = state; }
	void SetIndexNum(std::string& player_tag, IndexNum index_num)			{ PlayerParametor::Instance()._index_nums[player_tag] = index_num; }
	void SetKillCount(std::string& player_tag, int kill_count)				{ PlayerParametor::Instance()._player_params[player_tag].kill_count = kill_count; }

	//! ゲッター
	std::map<std::string, PlayerParam> GetAllParametor() const { return PlayerParametor::Instance()._player_params; }
	PlayerParam GetParametor(std::string& player_tag)    const { return PlayerParametor::Instance()._player_params[player_tag]; }
	int GetHitPoint(std::string& player_tag)			 const { return PlayerParametor::Instance()._player_params[player_tag].hit_point; }
	int GetAttackPowor(std::string& player_tag)			 const { return PlayerParametor::Instance()._player_params[player_tag].attack_powor; }
	float GetSpeed(std::string& player_tag)				 const { return PlayerParametor::Instance()._player_params[player_tag].speed; }
	int GetRankingPoint(std::string& player_tag)		 const { return PlayerParametor::Instance()._player_params[player_tag].ranking_point; }
	float GetAngle(std::string& player_tag)				 const { return PlayerParametor::Instance()._player_params[player_tag].angle; }
	Vector3 GetPosition(std::string& player_tag)		 const { return PlayerParametor::Instance()._player_params[player_tag].position; }
	int GetState(std::string& player_tag)				 const { return PlayerParametor::Instance()._player_params[player_tag].state; }
	IndexNum GetIndexNum(std::string& player_tag)        const { return PlayerParametor::Instance()._index_nums[player_tag]; }
	int GetKillCount(std::string& player_tag)			 const { return PlayerParametor::Instance()._player_params[player_tag].kill_count; }
};

class IArmData 
{
public:
	IArmData() {};
	~IArmData() {};

	//! セッター
	void SetArmParam(std::string& arm_tag, ArmParam& arm_param)				   { ArmParametor::Instance()._arm_params[arm_tag] = arm_param; }
	void SetAttackPowor(std::string& arm_tag, int attack_powor)				   { ArmParametor::Instance()._arm_params[arm_tag].attack_powor = attack_powor; }
	void SetGoSpeed(std::string& arm_tag, float speed)						   { ArmParametor::Instance()._arm_params[arm_tag].go_speed = speed; }
	void SetReturnSpeed(std::string& arm_tag, float speed)					   { ArmParametor::Instance()._arm_params[arm_tag].return_speed = speed; }
	void SetPosition(std::string& arm_tag, Vector3 pos)						   { ArmParametor::Instance()._arm_params[arm_tag].position = pos; }
	void SetAngle(std::string& arm_tag, float angle)						   { ArmParametor::Instance()._arm_params[arm_tag].angle = angle; }
	void SetState(std::string& arm_tag, int state)							   { ArmParametor::Instance()._arm_params[arm_tag].state = state; }
	void SetLimitRange(std::string& arm_tag, int limitrange)				   { ArmParametor::Instance()._arm_params[arm_tag].limit_range = limitrange; }
	void SetAnglePoint(std::string& arm_tag, std::vector<Vector3> angle_point) { ArmParametor::Instance()._arm_params[arm_tag].angle_point = angle_point; }

	//! ゲッター
	ArmParam GetPlayerPram(std::string& arm_tag)			 const { return ArmParametor::Instance()._arm_params[arm_tag]; }
	int GetAttackPowor(std::string& arm_tag)				 const { return ArmParametor::Instance()._arm_params[arm_tag].attack_powor; }
	float GetGoSpeed(std::string& arm_tag)					 const { return ArmParametor::Instance()._arm_params[arm_tag].go_speed; }
	float GetReturnSpeed(std::string& arm_tag)				 const { return ArmParametor::Instance()._arm_params[arm_tag].return_speed; }
	Vector3 GetPosition(std::string& arm_tag)				 const { return ArmParametor::Instance()._arm_params[arm_tag].position; }
	float GetAngle(std::string& arm_tag)					 const { return ArmParametor::Instance()._arm_params[arm_tag].angle; }
	int GetLimitRange(std::string& arm_tag)					 const { return ArmParametor::Instance()._arm_params[arm_tag].limit_range; }
	int GetState(std::string& arm_tag)						 const { return ArmParametor::Instance()._arm_params[arm_tag].state; }
	std::vector<Vector3> GetAnglePoint(std::string& arm_tag) const { return ArmParametor::Instance()._arm_params[arm_tag].angle_point; }
};

class IMapData {
public:
	IMapData() {};
	~IMapData() {};
	void SetData(std::vector<cstring> map_data) { MapParam::Instance()._map_data = map_data; }
	std::vector<cstring> GetData() const { return MapParam::Instance()._map_data; }
};