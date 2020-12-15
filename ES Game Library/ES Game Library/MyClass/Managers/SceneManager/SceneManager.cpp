#include "SceneManager.h"

//! 前方宣言
//! 余計なインクルードを減らすための手法
#include "../../Scenes/Main/MainScene.h"
#include "../../Scenes/Title/TitleScene.h"
#include"../../Scenes/Result/ResultScene.h"
#include "../ControllerManager/ContorollerManager.h"

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
	delete _result_data;
	delete _scene;
}

//! @brief シーンの切り替え関数
//! @param (scene) 遷移したいシーン 
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
	_result_data = new ResultData();

	return true;
}

int SceneManager::Update()
{
	_scene->Update();
	/**
* @brief カメラの初期設定
*/

	KeyboardState key = Keyboard->GetState();

	//SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);

//パース調整用
	if (key.IsKeyDown(Keys_A)) {
		_viewing_angle += 0.5;
	}
	if (key.IsKeyDown(Keys_Z)) {
		_viewing_angle -= 0.5;
	}
	if (key.IsKeyDown(Keys_S)) {
		_camera_pos.y += 0.1;
	}
	if (key.IsKeyDown(Keys_X)) {
		_camera_pos.y -= 0.1;
	}
	if (key.IsKeyDown(Keys_D)) {
		_camera_pos.z += 0.1;
	}
	if (key.IsKeyDown(Keys_C)) {
		_camera_pos.z -= 0.1;
	}
	if (key.IsKeyDown(Keys_F)) {
		_look_pos.x += 0.1;
	}
	if (key.IsKeyDown(Keys_V)) {
		_look_pos.x -= 0.1;
	}
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
	SceneCamera::Instance().SetSceneCamera();

	_scene->DrawAlpha3D();
}

void SceneManager::SetResultData(std::string tag, int points[PLAYER_COUNT_MAX]) {
	_result_data->tag = tag;
	
	for (int number = 0 ; number < PLAYER_COUNT_MAX;number++)
	{
		_result_data->points[number] = points[number];
	}
}

