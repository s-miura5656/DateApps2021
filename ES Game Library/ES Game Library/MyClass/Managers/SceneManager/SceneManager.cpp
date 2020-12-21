#include "SceneManager.h"

//! 前方宣言
//! 余計なインクルードを減らすための手法
#include "../../Scenes/Main/MainScene.h"
#include "../../Scenes/Title/TitleScene.h"
#include"../../Scenes/Result/ResultScene.h"
#include "../InputManager/InputManager.h"
#include "../TimeManager/Time.h"
#include "../ResouceManager/ResouceManager.h"

//! @brief コンストラクタ
//! @detail SceneManager が作られたときに呼び出されるよ
SceneManager::SceneManager()
{
	_scene = nullptr;
}

//! @brief デストラクタ
//! @detail SceneManager が消えるときに呼び出されるよ
SceneManager::~SceneManager()
{
	_result_data.reset();
	_scene.reset();
}

//! @brief シーンの切り替え関数
//! @param (scene) 遷移したいシーン 
void SceneManager::ChangeScene()
{
	if (_scene_state == _old_scene_state)
		return;

	if (_scene != nullptr) {
		_scene.reset();
	}

	switch (_scene_state) {
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

	_old_scene_state = _scene_state;
}

void SceneManager::SetSceneNumber(int scene_state)
{
	_scene_state = scene_state;
}

bool SceneManager::Initialize()
{
	InputManager::Instance().CreateXInputGamePad(PLAYER_TAG);

	_result_data.reset(new ResultData());

	_scene_state	 = 0;
	_old_scene_state = INT_MAX;

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

