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

//! ポイントテーブル
static const int BLOCK_POINT	   = 100;
static const int PLAYER_POINT	   = 300;
static const int LOST_PLAYER_POINT = 300;

//! リスポーン時間
static const int RESPAWN_TIME	   = 180;

//! 死ぬ前の硬直時間
static const int DEATH_RIGOR	   = 30;

//! リスポーン時のHPの定数
static const int RESPAWN_HITPOINT = 1000;

namespace PlayerEnum {
	enum Personality { NORMAL, ARM_RANGE, ARM_SPEED, PLAYER_MOVE_SPEED, PLAYER_DEFENCE, PERSONALITY_MAX};

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