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
	std::map<std::string, StageBase*> stages;
	std::vector<cstring> mapdate;//!�}�b�v�f�[�^�̓ǂݍ���
};