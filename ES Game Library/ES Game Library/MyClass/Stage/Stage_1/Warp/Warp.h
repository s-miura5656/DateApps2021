/**
 * @file Warp.h
 * @brief �X�e�[�W�x�[�X���p���������[�v���̃N���X
 * @author ��䐐��
 * @date 2020/12/11
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"
#include"../../../ParticleSystem/Particle.h"
class Warp :public StageBase
{
public:
	Warp(std::string tag);
	~Warp();
	bool Initialize() override;
	int Update() override;
	void Draw3D() override;
private:
	std::unique_ptr<ParticleSystem>_warp_effect;
	EFFECT _shader;
	int effect_time = 0;
};