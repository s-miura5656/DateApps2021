#include "SceneManager.h"

//! 前方宣言
//! 余計なインクルードを減らすための手法
#include "../../Scenes/Main/MainScene.h"
#include "../../Scenes/Title/TitleScene.h"
#include"../../Scenes/Result/ResultScene.h"
#include "../InputManager/InputManager.h"
#include "../TimeManager/Time.h"
#include "../ResouceManager/ResouceManager.h"
#include"../../Scenes/SelectScene/SelectScene.h"
#include"../../Managers/AudioManager/AudioManager.h"
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

	//!audio
	AudioManager::Instance().Initialize();

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
	case SceneState::SELECT:
		_scene.reset(new SelectScene);
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
//	InputManager::Instance().CreateXInputGamePad(PLAYER_TAG);

	InputManager::Instance().CreateDInputGamePad(PLAYER_TAG);

//	InputManager::Instance().CreateGamePad(PLAYER_TAG);

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

void SceneCamera::ShakeCamera()
{

	if (_time >= 60)
	{
		_camera->SetView(Vector3(7, 26.7f, -20.6f), Vector3(60.7, 0, 0));
		_shake_flag = true;
		return;
	}

	float x = 7 + ((60 / _time) * _num) * 0.01;

	_time++;
	_num *= -1;
	_camera->SetView(Vector3(x, 26.7f, -20.6f), Vector3(60.7, 0, 0));
}
