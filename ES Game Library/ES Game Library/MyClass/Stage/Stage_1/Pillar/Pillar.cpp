#include"Pillar.h"

Pillar::Pillar()
{
	_model = nullptr;
}

Pillar::~Pillar()
{

}

bool Pillar::Initialize()
{
	//X�t�@�C���̓ǂݍ���
	_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/Pillar.X"));
	//�X�P�[���̐ݒ�
	_model->SetScale(_scale);
	//�}�e���A���̐ݒ�
	_model->SetMaterial(GetMaterial());
	
	return _model != nullptr;
}