//! @file   StageBase.h
//! @brief  �X�e�[�W�p�̊��N���X
//! @author Souta_Miura
//! @date   2020/11/09

#pragma once

#include "../../ESGLib.h"

class StageBase
{
public:
	StageBase();
	virtual ~StageBase();

	virtual bool Initialize();
	virtual int Update();
	virtual void Draw2D();
	virtual void Draw3D();

protected:
	const float scale = 0.0254f;
	MODEL block;   //!���Ȃ�
	MODEL pillar;  //! ����
	MODEL map;     //! ��
	MODEL metal;   //! �O��
	int xz[13][15];//!�t�@�C���̓ǂݍ���
	char comma;	   //!�J���}�ǂݍ���
private:

};