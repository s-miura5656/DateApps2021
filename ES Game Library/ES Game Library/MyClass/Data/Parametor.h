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

	~PlayerParametor() {};

	static PlayerParametor& Instance() {
		static PlayerParametor instance;
		return instance;
	};

	void CreateParametor(std::string tag) { _player_params.emplace_hint(_player_params.end(), tag, _player_param); }
	void ResetParametor() { 
		_player_params.clear();
	}
	std::map<std::string, PlayerParam> _player_params;

private:
	PlayerParametor() {}
	PlayerParametor(const PlayerParametor&) = delete;
	void operator=(const PlayerParametor&)  = delete;

	std::map<std::string, IndexNum>  _index_nums;
	PlayerParam _player_param;
};

class ArmParametor
{
public:
	friend class IArmData;

	~ArmParametor() {};

	static ArmParametor& Instance() {
		static ArmParametor instance;
		return instance;
	};

	void CreateParametor(std::string tag) { _arm_params.emplace_hint(_arm_params.end(), tag, _arm_param); }
	void ResetParametor() { 
		_arm_params.clear(); 
	}

private:
	ArmParametor() {}
	ArmParametor(const ArmParametor&)   = delete;
	void operator=(const ArmParametor&) = delete;

	std::map<std::string, ArmParam> _arm_params;
	ArmParam _arm_param;

};

class MapParam {
public:
	friend class IMapData;
	~MapParam() {}

	static MapParam& Instance() {
		static MapParam instance;
		return instance;
	};
private:
	MapParam() {}
	MapParam(const MapParam&)		= delete;
	void operator=(const MapParam&) = delete;

	std::vector<cstring> _map_data;
	std::vector<int> _warp_suffix;
};