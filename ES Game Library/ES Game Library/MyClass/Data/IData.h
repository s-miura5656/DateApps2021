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

	void SetParametor(std::string& player_tag, PlayerParam& player_param)   { PlayerParametor::Instance()._player_params[player_tag] = player_param; }
	PlayerParam GetParametor(std::string& player_tag)				  const { return PlayerParametor::Instance()._player_params[player_tag]; }

	void SetHitPoint(std::string& player_tag, int hit_point)				{ PlayerParametor::Instance()._player_params[player_tag].hit_point = hit_point; }
	int GetHitPoint(std::string& player_tag)						  const { return PlayerParametor::Instance()._player_params[player_tag].hit_point; }

	void SetAttackPowor(std::string& player_tag, int attack_powor)			{ PlayerParametor::Instance()._player_params[player_tag].attack_powor = attack_powor; }
	int GetAttackPowor(std::string& player_tag)						  const { return PlayerParametor::Instance()._player_params[player_tag].attack_powor; }

	void SetSpeed(std::string& player_tag, float speed)						{ PlayerParametor::Instance()._player_params[player_tag].speed = speed; }
	float GetSpeed(std::string& player_tag)							  const { return PlayerParametor::Instance()._player_params[player_tag].speed; }

	void SetRankingPoint(std::string& player_tag, int ranking_point)		{ PlayerParametor::Instance()._player_params[player_tag].ranking_point = ranking_point; }
	int GetRankingPoint(std::string& player_tag)					  const { return PlayerParametor::Instance()._player_params[player_tag].ranking_point; }

	void SetAngle(std::string& player_tag, float angle)						{ PlayerParametor::Instance()._player_params[player_tag].angle = angle; }
	float GetAngle(std::string& player_tag)							  const { return PlayerParametor::Instance()._player_params[player_tag].angle; }

	void SetPosition(std::string& player_tag, Vector3 pos)					{ PlayerParametor::Instance()._player_params[player_tag].position = pos; }
	Vector3 GetPosition(std::string& player_tag)					  const { return PlayerParametor::Instance()._player_params[player_tag].position; }

	void SetState(std::string& player_tag, int state)						{ PlayerParametor::Instance()._player_params[player_tag].state = state; }
	int GetState(std::string& player_tag)							  const { return PlayerParametor::Instance()._player_params[player_tag].state; }

	void SetIndexNum(std::string& player_tag, IndexNum index_num)			{ PlayerParametor::Instance()._index_nums[player_tag] = index_num; }
	IndexNum GetIndexNum(std::string& player_tag)					  const { return PlayerParametor::Instance()._index_nums[player_tag]; }

	void SetKillCount(std::string& player_tag, int kill_count)				{ PlayerParametor::Instance()._player_params[player_tag].kill_count = kill_count; }
	int GetKillCount(std::string& player_tag)						  const { return PlayerParametor::Instance()._player_params[player_tag].kill_count; }

	void SetRankNum(std::string& player_tag, int rank_num) { PlayerParametor::Instance()._player_params[player_tag].rank_num = rank_num; }
	int GetRankNum(std::string& player_tag)						  const { return PlayerParametor::Instance()._player_params[player_tag].rank_num; }

	std::map<std::string, PlayerParam> GetAllParametor()			  const { return PlayerParametor::Instance()._player_params; }
};

class IArmData 
{
public:
	IArmData() {};
	~IArmData() {};

	void SetArmParam(std::string& arm_tag, ArmParam& arm_param)							  { ArmParametor::Instance()._arm_params[arm_tag] = arm_param; }
	ArmParam GetPlayerPram(std::string& arm_tag)									const { return ArmParametor::Instance()._arm_params[arm_tag]; }

	void SetAttackPowor(std::string& arm_tag, int attack_powor)							  { ArmParametor::Instance()._arm_params[arm_tag].attack_powor = attack_powor; }
	int GetAttackPowor(std::string& arm_tag)										const { return ArmParametor::Instance()._arm_params[arm_tag].attack_powor; }

	void SetGoSpeed(std::string& arm_tag, float speed)									  { ArmParametor::Instance()._arm_params[arm_tag].go_speed = speed; }
	float GetGoSpeed(std::string& arm_tag)											const { return ArmParametor::Instance()._arm_params[arm_tag].go_speed; }

	void SetReturnSpeed(std::string& arm_tag, float speed)								  { ArmParametor::Instance()._arm_params[arm_tag].return_speed = speed; }
	float GetReturnSpeed(std::string& arm_tag)										const { return ArmParametor::Instance()._arm_params[arm_tag].return_speed; }

	void SetPosition(std::string& arm_tag, Vector3 pos)									  { ArmParametor::Instance()._arm_params[arm_tag].position = pos; }
	Vector3 GetPosition(std::string& arm_tag)										const { return ArmParametor::Instance()._arm_params[arm_tag].position; }
	
	void SetAngle(std::string& arm_tag, float angle)									  { ArmParametor::Instance()._arm_params[arm_tag].angle = angle; }
	float GetAngle(std::string& arm_tag)											const { return ArmParametor::Instance()._arm_params[arm_tag].angle; }
	
	void SetState(std::string& arm_tag, int state)										  { ArmParametor::Instance()._arm_params[arm_tag].state = state; }
	int GetState(std::string& arm_tag)												const { return ArmParametor::Instance()._arm_params[arm_tag].state; }

	void SetLimitRange(std::string& arm_tag, int limitrange)							  { ArmParametor::Instance()._arm_params[arm_tag].limit_range = limitrange; }
	int GetLimitRange(std::string& arm_tag)											const { return ArmParametor::Instance()._arm_params[arm_tag].limit_range; }

	void SetAnglePositions(std::string& arm_tag, std::vector<Vector3> angle_positions)	  { ArmParametor::Instance()._arm_params[arm_tag].angle_position = angle_positions; }
	std::vector<Vector3> GetAnglePositions(std::string& arm_tag)					const { return ArmParametor::Instance()._arm_params[arm_tag].angle_position; }

	void SetAngles(std::string& arm_tag, std::vector<float> angles)						  { ArmParametor::Instance()._arm_params[arm_tag].angles = angles; }
	std::vector<float> GetAngles(std::string& arm_tag)								const { return ArmParametor::Instance()._arm_params[arm_tag].angles; }

	void SetHitPosition(std::string& arm_tag, Vector3 pos) { ArmParametor::Instance()._arm_params[arm_tag].hit_position = pos; }
	Vector3 GetHitPosition(std::string& arm_tag)									const { return ArmParametor::Instance()._arm_params[arm_tag].hit_position; }
};

class IMapData {
public:
	IMapData() {};
	~IMapData() {};
	void SetData(std::vector<cstring> map_data) { MapParam::Instance()._map_data = map_data; }
	std::vector<cstring> GetData() const { return MapParam::Instance()._map_data; }

	void SetWarp(std::vector<int> warp_suffix) { MapParam::Instance()._warp_suffix = warp_suffix; }
	std::vector<int> GetWarp() const { return MapParam::Instance()._warp_suffix; }
};