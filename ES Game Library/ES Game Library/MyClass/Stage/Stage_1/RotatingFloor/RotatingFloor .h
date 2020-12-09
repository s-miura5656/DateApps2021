/**
 * @file Floor.h
 * @brief �X�e�[�W�x�[�X���p�������O�ǂ̃N���X
 * @author ��䐐��
 * @date 2020/11/11
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"

class RotatingFloor :public StageBase
{
public:
	RotatingFloor(std::string tag);
	~RotatingFloor();
	bool Initialize() override;
	int Update() override;
	void Draw3D() override;
private:
	int rotation;
};