#pragma once


#include "../../ESGLib.h"

class Item{
public:
	

	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();
	

	bool SetState();

private:
	// �ϐ��錾

	// @brief�@���f��
	MODEL block;
	MODEL metal;

	// @brief �����蔻��p�̔�
	MODEL block_hitbox;
	MODEL metal_hitbox;

	// @brief �u���b�N�ƃA�C�e���؂�ւ��p�̃t���O
	bool block_state;
	bool metal_state;

	// @brief �����蔻��p�̔�
	OrientedBoundingBox block_obb;
	OrientedBoundingBox metal_obb;


	// �֐��v���g�^�C�v

};
