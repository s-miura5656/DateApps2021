
#include"Floor.h"
Floor::Floor()
{
	block_base = nullptr;
}

Floor::~Floor()
{

}

bool Floor::Initialize()
{
	//X�t�@�C���̓ǂݍ���
	block_base = GraphicsDevice.CreateModelFromFile(_T("MapSprite/ground.X"));
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