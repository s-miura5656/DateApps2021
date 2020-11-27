//! @file   Parametor.h
//! @brief  各キャラクターのパラメーターのクラス
//! @author Souta_Miura
//! @date   2020/11/06

#pragma once

#include "../../ESGLib.h"
#include "StructList.h"

class PlayerParametor
{
public:
	friend class IPrayerData;

	PlayerParametor() {}
	~PlayerParametor() {};

	static PlayerParametor& Instance() {
		static PlayerParametor instance;
		return instance;
	};

	void CreateParametor(std::string name) { _player_params.emplace(name, _player_param); }

private:
	PlayerParametor(const PlayerParametor&) = delete;
	void operator=(const PlayerParametor&) = delete;

	std::map<std::string, PlayerParam> _player_params;
	IndexNum _index_num;
	PlayerParam _player_param;
};

class ArmParametor
{
public:
	friend class IArmData;

	ArmParametor() {}
	~ArmParametor() {};

	static ArmParametor& Instance() {
		static ArmParametor instance;
		return instance;
	};

	void CreateParametor(std::string name) { _arm_params.emplace(name, _arm_param); }
private:
	ArmParametor(const ArmParametor&) = delete;
	void operator=(const ArmParametor&) = delete;

	std::map<std::string, ArmParam> _arm_params;
	ArmParam _arm_param;

};

class MapParam {
public:
	friend class IMapData;
	MapParam() {}
	~MapParam() {}

	static MapParam& Instance() {
		static MapParam instance;
		return instance;
	};
private:
	MapParam(const MapParam&) = delete;
	void operator=(const MapParam&) = delete;

	std::vector<cstring> _map_data;
};