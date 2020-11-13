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

	virtual bool Initialize() { return true; };
	virtual int Update();
	virtual void Draw3D();
	Material GetMaterial();

	//�����ŃX�e�[�W���\������u���b�N�̃|�W�V�������Z�b�g����
	void SetPosition(Vector3& position) { _position = position; }
	//�X�e�[�W���\������u���b�N�̃|�W�V�������擾����
	Vector3 GetPosition() { return _position; }
	//�X�e�[�W���\������u���b�N�̔j��t���O���Z�b�g����
	void SetDestructionFlag(bool& destruction_flag) { _destruction_flag = destruction_flag; }
	//�X�e�[�W���\������u���b�N�̔j��t���O���擾����
	bool GetDestructionFlag() { return _destruction_flag; }
protected:
	const float scale = 0.0254f;//!��̃X�P�[����ݒ肷��
	bool _destruction_flag = true;//!false�Ŕj�󂳂��j��t���O
	MODEL block_base;//!�p������郂�f���̃x�[�X
	Vector3 _position;//!�p������郂�f���̃|�W�V����
private:

};