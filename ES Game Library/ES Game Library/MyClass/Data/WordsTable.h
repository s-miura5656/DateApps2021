#pragma once

#include "../../ESGLib.h"

//! �v���C���[�̍ő吔
static const auto PLAYER_COUNT_MAX = 4;

//! �A�z�z��p�^�O
static const std::string PLAYER_TAG = "Player_";
static const std::string ARM_TAG	= "Arm_";
static const std::string ITEM_TAG	= "Item_";

//! �A�C�e���̎�ޔ��ʗp
static const std::string POWOR_ITEM_TAG    = "AttackItem_";
static const std::string SPEED_ITEM_TAG	   = "SpeedItem_";
static const std::string HITPOINT_ITEM_TAG = "HitPointItem_";

//! �u���b�N�̎�ޔ��ʗp
static const std::string DESTRUCTION_BLOCK_TAG    = "DestructionBlock_";
static const std::string INDESTRUCTIBIEPILLAR_TAG = "InDestructiblePillar_";
static const std::string WALL_METAL_TAG           = "WallMetal_";
static const std::string FLOOR_TAG                = "Floor_";

namespace PlayerEnum {
	//�v���C���[�̃A�j���[�V����
	enum { WAIT, MOVE, DESTRUCTION, ATTACK, ANIMATION_ALL_TYPE };

	enum PunchType { UNCLASP_PUNCH, SET_PUNCH, PUNCH_MAX };

	enum { DEATH, ALIVE };
}

namespace ArmEnum {
	enum PunchState { NO_PUNCH, PUNCH, RETURN_PUNCH };
}