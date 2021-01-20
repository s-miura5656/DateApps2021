#pragma once

#include "../../ESGLib.h"

//! プレイヤーの最大数
static const int PLAYER_COUNT_MAX = 4;

//! 連想配列用タグ
static const std::string PLAYER_TAG = "Player_";
static const std::string ARM_TAG	= "Arm_";
static const std::string ITEM_TAG	= "Item_";

//! アイテムの種類判別用
static const std::string NULL_ITEM_TAG	   = "NullItem";
static const std::string POINT_ITEM_TAG    = "PointItem_";
static const std::string POWOR_ITEM_TAG    = "AttackItem_";
static const std::string SPEED_ITEM_TAG	   = "SpeedItem_";
static const std::string HITPOINT_ITEM_TAG = "HitPointItem_";

//! ブロックの種類判別用
static const std::string DESTRUCTION_BLOCK_TAG    = "DestructionBlock_";
static const std::string INDESTRUCTIBIEPILLAR_TAG = "InDestructiblePillar_";
static const std::string WALL_METAL_TAG           = "WallMetal_";
static const std::string ROTATION_FLOOR_TAG		  = "RotationFloor_";
static const std::string WARP_TAG				  = "Warp_";

//!アイテムの種類のタグ
static const std::string ITEM_PLAYER_SPEEDUP = "Item_player_speedup";
static const std::string ITEM_ARM_SPEEDUP    = "Item_arm_speedup";
static const std::string ITEM_POWERDOWN      = "Item_powerdown_";
static const std::string ITEM_THUNDER        = "Item_thunder_";
//! ポイントテーブル
static const int BLOCK_POINT	   = 100;
static const int PLAYER_POINT	   = 600;
static const int LOST_PLAYER_POINT = 600;

static const int FIRST_RANK_POINT  = 1000;
static const int SECOND_RANK_POINT = 600;
static const int THIRD_RANK_POINT  = 400;
static const int FOURTH_RANK_POINT = 200;
//! リスポーン時間
static const int RESPAWN_TIME	   = 180;

//! 死ぬ前の硬直時間
static const int DEATH_RIGOR	   = 30;

//! リスポーン時のHPの定数
static const int RESPAWN_HITPOINT = 1000;

//! アームの最大距離到達時の硬直
static const int ARM_MAX_DISTANCE_RIGOR = 30;

//!無敵時間の秒数
static const int INVINCIBLE_FRAME = 120;

//!ランダムで降ってくるブロックの個数
static const int FALL_BLOCK_COUNT = 10;

//!ランダムで降ってくるブロックの頻度
static const int FALL_BLOCK_INTERVAL = 60;

//!いつまで強化されているかparameter_change_count
static const int POWERUP_TIME = 600;

//!いつまで弱体化されているかparameter_change_count
static const int POWERDOWN_TIME = 300;

//!1位の弱体化する確率
static const int WEAK_PROBABILITY_NUMBER = 50;

//!何秒経過後にリザルトへ遷移するか
static const int RESULT_GO_TIME = 3;

namespace PlayerEnum {
	enum Personality { NORMAL, ARM_RANGE, ARM_SPEED, PLAYER_MOVE_SPEED, PLAYER_DEFENCE, PLAYER_KING,PERSONALITY_MAX};

	//プレイヤーのアニメーション
	enum Animation { WAIT, MOVE, SHOT, ATTACK, DAMAGE, DEATH, ANIMATION_ALL_TYPE };

	enum PunchType { UNCLASP_PUNCH, SET_PUNCH, PUNCH_MAX };

	//enum { DEATH, ALIVE };
}

namespace ArmEnum {
	enum PunchState { NO_PUNCH, PUNCH, WAIT_PUNCH, RETURN_PUNCH };
	enum PunchType { PULL, PUSH, ALL };
}

namespace EffectEnum {
	enum EffectType{ PUNCH, HIT, ALL_TYPE};
}