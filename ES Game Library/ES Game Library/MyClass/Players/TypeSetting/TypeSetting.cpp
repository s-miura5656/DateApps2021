#include "TypeSetting.h"
#include "../../Data/WordsTable.h"
#include "../../Data/IData.h"

TypeSetting::TypeSetting()
{
}

TypeSetting::~TypeSetting()
{
}

void TypeSetting::Initialize()
{
	_charactor_params[PlayerEnum::Personality::ARM_RANGE]		  = ArmRangeType();
	_charactor_params[PlayerEnum::Personality::ARM_SPEED]		  = ArmSpeedType();
	_charactor_params[PlayerEnum::Personality::PLAYER_MOVE_SPEED] = PlayerMoveSpeedType();
	_charactor_params[PlayerEnum::Personality::PLAYER_DEFENCE]	  = PlayerDefenceType();
}

CharactorParam TypeSetting::ArmRangeType()
{
	CharactorParam type_param;

	type_param.personality = PlayerEnum::Personality::ARM_RANGE;

	type_param.arm_param.limit_range = 15;
	type_param.arm_param.turn_frame  = 15;

	return type_param;
}

CharactorParam TypeSetting::ArmSpeedType()
{
	CharactorParam type_param;

	type_param.personality = PlayerEnum::Personality::ARM_SPEED;

	type_param.player_param.shot_rigor_frame = 60;

	type_param.arm_param.go_speed			 = 0.2f;
	type_param.arm_param.limit_range		 = 7;

	return type_param;
}

CharactorParam TypeSetting::PlayerMoveSpeedType()
{
	CharactorParam type_param;

	type_param.personality = PlayerEnum::Personality::PLAYER_MOVE_SPEED;

	type_param.player_param.speed    = 0.08f;

	type_param.arm_param.limit_range = 5;

	return type_param;
}

CharactorParam TypeSetting::PlayerDefenceType()
{
	CharactorParam type_param;

	type_param.personality = PlayerEnum::Personality::PLAYER_DEFENCE;

	type_param.player_param.hit_point = 2000;

	type_param.player_param.shot_rigor_frame = 15;

	return type_param;
}
