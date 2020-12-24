#include "Blinking.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Data/IData.h"
#include "../../../Data/WordsTable.h"
#include "../../../Managers/SceneManager/SceneManager.h"
#include "../../../ParticleSystem/Particle.h"

Blinking::Blinking()
{
	_model  = nullptr;
}

Blinking::~Blinking()
{

}

bool Blinking::Initialize(Vector3 pos)
{
	//!X�t�@�C���̓ǂݍ���
	_model  = ResouceManager::Instance().LoadModelFile(_T("MapSprite/blinking.X"));

	//!�X�P�[���̐ݒ�
	_scale = 1.0f;
	_model->SetScale(_scale);

	//!�|�W�V�������~���Ă���u���b�N�Ɠ����ɐݒ肷��
	_position = pos;

	//!�}�e���A���̐ݒ�
	Material mat;
	mat.Diffuse  = Color(0.5f, 0.5f, 0.5f);
	mat.Ambient  = Color(1.0f, 1.0f, 1.0f);
	mat.Specular = Color(0.5f, 0.5f, 0.5f);
	_model->SetMaterial(mat);

	return _model != nullptr;
}
int Blinking::Update()
{
	_position.y = 0.1;

	return 0;
}

void Blinking::Draw3D()
{
	_model->SetPosition(_position);
	_model->SetRotation(0, 0, 0);
	_model->Draw();
}