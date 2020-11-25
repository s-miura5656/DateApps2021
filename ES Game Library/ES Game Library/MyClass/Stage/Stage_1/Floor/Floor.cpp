
#include"Floor.h"
Floor::Floor()
{
	_model = nullptr;
}

Floor::~Floor()
{

}

bool Floor::Initialize()
{
	//X�t�@�C���̓ǂݍ���
	_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/stage.X"));
	//�X�P�[���̐ݒ�
	_model->SetScale(_scale);
	//�}�e���A���̐ݒ�
	_model->SetMaterial(GetMaterial());
	
	return _model != nullptr;
}