//! @file   PlayerParametor.h
//! @brief  プレイヤーのパラメーターのクラス
//! @author Souta_Miura
//! @date   2020/11/06

#pragma once

#include "../../../ESGLib.h"
#include "../../Data/StructList.h"

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
	void CreateArmModel(std::string name) { _arms_pos.emplace(name, _arm_pos); }
private:
	PlayerParametor(const PlayerParametor&) = delete;
	void operator=(const PlayerParametor&) = delete;

	std::map<std::string, PlayerParam> _player_params;
	std::map<std::string, Vector3> _arms_pos;
	PlayerParam _player_param;
	Vector3 _arm_pos;
};