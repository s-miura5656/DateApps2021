/**
 * @file Floor.h
 * @brief �X�e�[�W�x�[�X���p���������̃N���X
 * @author ��䐐��
 * @date 2020/11/11
 */
#pragma once

#include"../../../ESGLib.h"
#include"../StageBase.h"
class Floor :public StageBase
{
public:
	Floor();
	~Floor();
	bool Initialize() override;
private:
};