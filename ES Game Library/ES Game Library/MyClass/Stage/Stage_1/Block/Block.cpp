#include"Block.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"

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
	//_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/capsule.X"));
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/capsule.X"));
	//�X�P�[���̐ݒ�
	_model->SetScale(_scale);
	//�}�e���A���̐ݒ�
	_model->SetMaterial(GetMaterial());
	return _model != nullptr;
}

void Block::Draw3D()
{
	if (_destructiveflag)
	{
		StageBase::Draw3D();
	}
}

