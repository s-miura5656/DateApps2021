#include"Metal.h"

Metal::Metal()
{
	block_base = nullptr;
}

Metal::~Metal()
{

}

bool Metal::Initialize()
{
	//X�t�@�C���̓ǂݍ���
	block_base = GraphicsDevice.CreateModelFromFile(_T("MapSprite/metal.X"));
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