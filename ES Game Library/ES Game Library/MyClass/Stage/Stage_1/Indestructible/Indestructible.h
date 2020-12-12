/**
 * @file Indestructible.h
 * @brief �X�e�[�W�x�[�X���p�������j��ł��Ȃ��X�e�[�W�u���b�N
 * @author ��䐐��
 * @date 2020/11/26
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"

class Indestructible :public StageBase
{
public:
	Indestructible();
	~Indestructible();
	bool Initialize() override;
	void Draw3D() override;
private:
};