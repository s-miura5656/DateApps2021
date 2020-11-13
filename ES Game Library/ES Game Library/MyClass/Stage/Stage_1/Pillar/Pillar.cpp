#include"Pillar.h"

Pillar::Pillar()
{
	block_base = nullptr;
}

Pillar::~Pillar()
{

}

bool Pillar::Initialize()
{
	//X�t�@�C���̓ǂݍ���
	block_base = GraphicsDevice.CreateModelFromFile(_T("MapSprite/Pillar.X"));
	//�X�P�[���̐ݒ�
	block_base->SetScale(scale);
	//�}�e���A���̐ݒ�
	block_base->SetMaterial(GetMaterial());
	if (nullptr == block_base)
	{
		return false;
	}
	return true;
}