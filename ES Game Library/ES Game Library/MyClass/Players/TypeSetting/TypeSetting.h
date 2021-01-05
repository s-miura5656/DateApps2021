#pragma once

#include "../../../ESGLib.h"
#include "../../Data/StructList.h"
#include "../../Data/WordsTable.h"

class TypeSetting
{
public:
	~TypeSetting();

	void Initialize();

	static TypeSetting& Instance() {
		static TypeSetting instance;
		return instance;
	};

	void SetPlayerType(std::string player_tag, int type) { _player_type.emplace_hint(_player_type.end(), player_tag, type); }
	int GetPlayerType(std::string player_tag)			 { return _player_type[player_tag]; }

	CharactorParam GetCharactorParam(int player_type)	 { return _charactor_params[player_type]; }
private:
	TypeSetting();
	TypeSetting(const TypeSetting&)		= delete;
	void operator=(const TypeSetting&)  = delete;

	CharactorParam ArmRangeType();
	CharactorParam ArmSpeedType();
	CharactorParam PlayerMoveSpeedType();
	CharactorParam PlayerDefenceType();
	CharactorParam ParametorMaxType();

	std::map<std::string, int> _player_type;
	CharactorParam _charactor_params[PlayerEnum::Personality::PERSONALITY_MAX];
};