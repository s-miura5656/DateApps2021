/**
 * @file Indestructible.h
 * @brief �X�e�[�W�x�[�X���p�������j��ł��Ȃ��X�e�[�W�u���b�N
 * @author ��䐐��
 * @date 2020/11/26
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"
#include "../../../Data/IData.h"
class Indestructible :public StageBase
{
public:
	Indestructible(std::string tag);
	~Indestructible();
	bool Initialize() override;
	int Update() override;
	void Draw3D() override;
private:
	std::unique_ptr<IArmData>		_i_arm_data;
	float                           _speed = 0.05;
	bool                            _move_flag = false;
};