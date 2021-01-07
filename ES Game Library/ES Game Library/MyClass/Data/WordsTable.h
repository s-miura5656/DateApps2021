#pragma once

#include "../../ESGLib.h"

//! �v���C���[�̍ő吔
static const int PLAYER_COUNT_MAX = 4;

//! �A�z�z��p�^�O
static const std::string PLAYER_TAG = "Player_";
static const std::string ARM_TAG	= "Arm_";
static const std::string ITEM_TAG	= "Item_";

//! �A�C�e���̎�ޔ��ʗp
static const std::string NULL_ITEM_TAG	   = "NullItem";
static const std::string POINT_ITEM_TAG    = "PointItem_";
static const std::string POWOR_ITEM_TAG    = "AttackItem_";
static const std::string SPEED_ITEM_TAG	   = "SpeedItem_";
static const std::string HITPOINT_ITEM_TAG = "HitPointItem_";

//! �u���b�N�̎�ޔ��ʗp
static const std::string DESTRUCTION_BLOCK_TAG    = "DestructionBlock_";
static const std::string INDESTRUCTIBIEPILLAR_TAG = "InDestructiblePillar_";
static const std::string WALL_METAL_TAG           = "WallMetal_";
static const std::string ROTATION_FLOOR_TAG		  = "RotationFloor_";
static const std::string WARP_TAG				  = "Warp_";

//! �|�C���g�e�[�u��
static const int BLOCK_POINT	   = 100;
static const int PLAYER_POINT	   = 600;
static const int LOST_PLAYER_POINT = 600;

//! ���X�|�[������
static const int RESPAWN_TIME	   = 180;

//! ���ʑO�̍d������
static const int DEATH_RIGOR	   = 30;

//! ���X�|�[������HP�̒萔
static const int RESPAWN_HITPOINT = 1000;

//! �A�[���̍ő勗�����B���̍d��
static const int ARM_MAX_DISTANCE_RIGOR = 30;

//!���G���Ԃ̕b��
static const int INVINCIBLE_FRAME = 120;

//!�����_���ō~���Ă���u���b�N�̌�
static const int FALL_BLOCK_COUNT = 10;

//!�����_���ō~���Ă���u���b�N�̕p�x
static const int FALL_BLOCK_INTERVAL = 1200;

//!���܂ŋ�������Ă��邩parameter_change_count
static const int POWERUP_TIME = 600;

//!���܂Ŏ�̉�����Ă��邩parameter_change_count
static const int POWERDOWN_TIME = 300;
namespace PlayerEnum {
	enum Personality { NORMAL, ARM_RANGE, ARM_SPEED, PLAYER_MOVE_SPEED, PLAYER_DEFENCE, PLAYER_KING,PERSONALITY_MAX};

	//�v���C���[�̃A�j���[�V����
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