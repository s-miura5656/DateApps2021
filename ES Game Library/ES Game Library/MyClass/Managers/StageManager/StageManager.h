//! @file   StageBase.h
//! @brief  �X�e�[�W�p�̊Ǘ��N���X
//! @author Souta_Miura
//! @date   2020/11/09

#pragma once

#include"../ManagerBase.h"
#include"../../Stage/Block/Block.h"
#include"../../Stage/Pillar/Pillar.h"
#include"../../Stage/Metal/Metal.h"
#include"../../Stage/Floor/Floor.h"
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
	std::vector<cstring> mapdate;
	char comma;	   //!�J���}�ǂݍ���
	char xz[13][15];
	int* matrix;
	int i, j, n, m;
};