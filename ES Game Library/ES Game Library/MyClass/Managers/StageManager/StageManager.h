//! @file   StageBase.h
//! @brief  �X�e�[�W�p�̊Ǘ��N���X
//! @author Souta_Miura
//! @date   2020/11/09

#pragma once

#include"../../Managers/ManagerBase.h"
#include"../../Stage/Stage_1/Block/Block.h"
#include"../../Stage/Stage_1/Pillar/Pillar.h"
#include"../../Stage/Stage_1/Metal/Metal.h"
#include"../../Stage/Stage_1/Floor/Floor.h"

class StageBase;

class StageManager : public ManagerBase
{
public:
	StageManager();
	~StageManager();

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;

private:
	Block* block;
	Pillar* pillar;
	Metal* metal;
	Floor*floor;
	char comma;	   //!�J���}�ǂݍ���
	int xz[13][15];//!�t�@�C���̓ǂݍ���
};