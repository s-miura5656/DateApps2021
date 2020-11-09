//! @file   StageBase.h
//! @brief  �X�e�[�W�p�̊Ǘ��N���X
//! @author Souta_Miura
//! @date   2020/11/09

#pragma once

#include"../ManagerBase.h"

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
	StageBase* _stage;
};