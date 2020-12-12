//! @file   StageBase.h
//! @brief  �X�e�[�W�p�̊��N���X
//! @author Souta_Miura
//! @date   2020/11/09
#pragma once

#include "../../ESGLib.h"
#include "../Collision/HitBox.h"

class StageBase
{
public:
	StageBase();
	virtual ~StageBase();

	virtual bool Initialize() { return true; };
	virtual int Update();
	virtual void Draw3D();
	virtual void DrawAlpha3D();

	Material GetMaterial();

	//�����ŃX�e�[�W���\������u���b�N�̃|�W�V�������Z�b�g����
	void SetPosition(Vector3& position) { _position = position; }
	//�X�e�[�W���\������u���b�N�̃|�W�V�������擾����
	Vector3 GetPosition() { return _position; }
protected:
	MODEL _model;//!�p������郂�f���̃x�[�X
	EFFECT _shader;

	float _scale = 1.0f;
	Vector3 _position;//!�p������郂�f���̃|�W�V����
	
	std::unique_ptr<HitBox> _hit_box;
	std::string _tag;

private:
};