#include "SceneManager.h"

//! �O���錾
//! �]�v�ȃC���N���[�h�����炷���߂̎�@
#include "../../Scenes/Main/MainScene.h"
#include "../../Scenes/Title/TitleScene.h"
#include"../../Scenes/Result/ResultScene.h"

//! @brief �R���X�g���N�^
//! @detail SceneManager �����ꂽ�Ƃ��ɌĂяo������
SceneManager::SceneManager()
{
	_scene = nullptr;
}

//! @brief �f�X�g���N�^
//! @detail SceneManager ��������Ƃ��ɌĂяo������
SceneManager::~SceneManager()
{
	delete _scene;
}

//! @brief �V�[���̐؂�ւ��֐�
//! @param (scene) �J�ڂ������V�[�� 
void SceneManager::ChangeScene(SceneState scene)
{
	//! 
	if (_scene != nullptr) {
		delete _scene;
	}
	
	switch (scene) {
	case SceneState::TITLE:
		_scene = new TitleScene;
		break;
	case SceneState::MAIN:
		_scene = new MainScene;
		break;
	case SceneState::RESULT:
		_scene = new ResultScene;
		break;
	}

	_scene->Initialize();
}

bool SceneManager::Initialize()
{
	//! ��ԍŏ��ɓǂݍ��܂��V�[��
	ChangeScene(SceneState::MAIN);

	return true;
}

int SceneManager::Update()
{
	_scene->Update();

	return 0;
}

void SceneManager::Draw2D()
{
	
	_scene->Draw2D();
}

void SceneManager::Draw3D()
{
	_scene->Draw3D();
}


