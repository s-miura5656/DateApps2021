#include"WallCorner.h"

WallCorner::WallCorner()
{
	_model = nullptr;
}

WallCorner::~WallCorner()
{

}

bool WallCorner::Initialize()
{
	//X�t�@�C���̓ǂݍ���
	_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/wal_corner.X"));
	//�X�P�[���̐ݒ�
	_model->SetScale(_scale);
	//�}�e���A���̐ݒ�
	_model->SetMaterial(GetMaterial());
	return _model != nullptr;
}