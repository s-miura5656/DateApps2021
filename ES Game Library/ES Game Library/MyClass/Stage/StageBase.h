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
	Material GetMaterial();

	//�����ŃX�e�[�W���\������u���b�N�̃|�W�V�������Z�b�g����
	void SetPosition(Vector3& position) { _position = position; }
	//�����ŃX�e�[�W���\������u���b�N�̃��[�e�[�V�������Z�b�g����
	void SetRotation(Vector3& rotation) { _rotation = rotation; }
	//�X�e�[�W���\������u���b�N�̃|�W�V�������擾����
	Vector3 GetPosition() { return _position; }
	bool IsFlag() const { return Removeflag; };
	std::string GetTag() const { return _tag; }
protected:
	const float _scale = 1.0f;//!��̃X�P�[����ݒ肷��
	MODEL _model;//!�p������郂�f���̃x�[�X
	Vector3 _position;//!�p������郂�f���̃|�W�V����
	Vector3 _rotation;//!�p������郂�f���̃��[�e�[�V����
	std::unique_ptr<HitBox> _hit_box;
	std::string _tag;
	bool Removeflag = false;
private:

};