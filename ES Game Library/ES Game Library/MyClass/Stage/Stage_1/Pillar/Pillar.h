/**
 * @file Pillar.h
 * @brief �X�e�[�W�x�[�X���p�������j��ł��Ȃ��u���b�N�̃N���X
 * @author ��䐐��
 * @date 2020/11/11
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"

class Pillar :public StageBase
{
public:
	Pillar(std::string tag);
	~Pillar();
	bool Initialize() override;


private:
};