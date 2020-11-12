#pragma once

#include "../../ESGLib.h"

//! プレイヤーの最大数
static const auto PLAYER_COUNT_MAX = 4;

//! 連想配列用タグ
static const std::string PLAYER_TAG = "Player_";
static const std::string ARM_TAG	= "Arm_";
static const std::string ITEM_TAG	= "Item_";

//! アイテムの種類判別用
static const std::string POWOR_ITEM_TAG    = "AttackItem_";
static const std::string SPEED_ITEM_TAG	   = "SpeedItem_";
static const std::string HITPOINT_ITEM_TAG = "HitPointItem_";

//! アイテムの状態ステート
enum { OK, END };

namespace PlayerEnum {
	//プレイヤーのアニメーション
	enum { WAIT, WALK, DESTRUCTION, ATTACK, ANIMATION_ALL_TYPE };

	enum PunchType { UNCLASP_PUNCH, SET_PUNCH, PUNCH_MAX };

	//プレイヤーの状態
	enum { NO_PUNCH, PUNCH, RETURN_PUNCH };
	enum { DEATH, ALIVE };

	//gamepad
	enum { PLAYER1, PLAYER2, PLAYER3, PLAYER4, PLAYER_MAX };
}