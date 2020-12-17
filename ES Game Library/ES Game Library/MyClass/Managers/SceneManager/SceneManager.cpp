#include "SceneManager.h"

//! �O���錾
//! �]�v�ȃC���N���[�h�����炷���߂̎�@
#include "../../Scenes/Main/MainScene.h"
#include "../../Scenes/Title/TitleScene.h"
#include"../../Scenes/Result/ResultScene.h"
#include "../ControllerManager/ContorollerManager.h"
#include "../TimeManager/Time.h"
#include "../ResouceManager/ResouceManager.h"

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
	_result_data.reset();
	_scene.reset();
}

//! @brief �V�[���̐؂�ւ��֐�
//! @param (scene) �J�ڂ������V�[�� 
void SceneManager::ChangeScene(SceneState scene)
{
	if (_scene != nullptr) {
		_scene.reset();
	}
	
	switch (scene) {
	case SceneState::TITLE:
		_scene.reset(new TitleScene);
		break;
	case SceneState::MAIN:
		_scene.reset(new MainScene);
		break;
	case SceneState::RESULT:
		_scene.reset(new ResultScene);
		break;
	}

	TimeManager::Instance().Initialize();

	_scene->Initialize();
}

bool SceneManager::Initialize()
{
	ControllerManager::Instance().SetGamePadMaxCount(PLAYER_COUNT_MAX);

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);

		ControllerManager::Instance().CreateGamePad(tag);
	}

	_result_data.reset(new ResultData());

	return true;
}

int SceneManager::Update()
{
	TimeManager::Instance().Update();

	_scene->Update();

	return 0;
}

void SceneManager::Draw2D()
{
	_scene->Draw2D();
}

void SceneManager::Draw3D()
{
	SceneCamera::Instance().SetSceneCamera();
	
	_scene->Draw3D();
}

void SceneManager::DrawAlpha3D()
{
	_scene->DrawAlpha3D();
}

void SceneManager::SetResultData(int ranknum[PLAYER_COUNT_MAX], int points[PLAYER_COUNT_MAX]) {
	
	for (int number = 0 ; number < PLAYER_COUNT_MAX;number++)
	{
		_result_data->ranknum[number] = ranknum[number];
		_result_data->points[number] = points[number];
	}
}

