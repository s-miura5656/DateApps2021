#include"Block.h"

Block::Block()
{
	block_base = nullptr;
}

Block::~Block()
{

}

bool Block::Initialize()
{
	//X�t�@�C���̓ǂݍ���
	block_base = GraphicsDevice.CreateModelFromFile(_T("MapSprite/block.X"));
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

