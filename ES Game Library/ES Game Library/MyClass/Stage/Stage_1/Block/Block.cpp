#include"Block.h"

Block::Block()
{
	_model = nullptr;
}

Block::~Block()
{

}

bool Block::Initialize()
{
	//X�t�@�C���̓ǂݍ���
	_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/block.X"));
	//�X�P�[���̐ݒ�
	_model->SetScale(_scale);
	//�}�e���A���̐ݒ�
	_model->SetMaterial(GetMaterial());

	return _model != nullptr;
}

