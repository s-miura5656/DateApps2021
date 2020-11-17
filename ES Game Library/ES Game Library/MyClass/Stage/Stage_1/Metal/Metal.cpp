#include"Metal.h"

Metal::Metal()
{
	_model = nullptr;
}

Metal::~Metal()
{

}

bool Metal::Initialize()
{
	//X�t�@�C���̓ǂݍ���
	_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/metal.X"));
	//�X�P�[���̐ݒ�
	_model->SetScale(_scale);
	//�}�e���A���̐ݒ�
	_model->SetMaterial(GetMaterial());
	
	return _model != nullptr;
}