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
	/**
	* @brief ライトの初期設定
	*/
	Light light;
	light.Type = Light_Directional;
	light.Direction = Vector3(0, 1, 1);
	light.Diffuse = Color(1.0f, 1.0f, 1.0f);
	light.Ambient = Color(1.0f, 1.0f, 1.0f);
	light.Specular = Color(1.0f, 1.0f, 1.0f);
	GraphicsDevice.SetLight(light);

	/**
	* @brief カメラの初期設定
	*/
	Viewport view = GraphicsDevice.GetViewport();
	_camera_pos = Vector3(7, 600, -400);
	_look_pos   = Vector3(7, 0, -5.5f);

	_camera->SetLookAt(_camera_pos, _look_pos, 0);
	_camera->SetPerspectiveFieldOfView(1.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);
	GraphicsDevice.SetCamera(_camera);
	
	Effekseer.Attach(GraphicsDevice);

	//! 一番最初に読み込まれるシーン
	ChangeScene(SceneState::MAIN);

	return true;
}

int SceneManager::Update()
{
	_scene->Update();

#if  _DEBUG

	/*if (ControllerManager::Instance().GetController("Player_1") != nullptr)
	{
		auto&& pad = ControllerManager::Instance().GetController("Player_1");

		if (pad->GetButtonState(GamePad_Button6))
		{
			_camera_pos.y++;
		}

		if (pad->GetButtonState(GamePad_Button8))
		{
			_camera_pos.y--;
		}

		if (pad->GetButtonState(GamePad_Button5))
		{
			_camera_pos.z++;
		}

		if (pad->GetButtonState(GamePad_Button7))
		{
			_camera_pos.z--;
		}
	}*/
	
	//_camera->SetLookAt(_camera_pos, Vector3(7, 0, -5.5f), 0);

#endif //  _DEBUG

	return 0;
}

void SceneManager::Draw2D()
{
	_scene->Draw2D();
}

void SceneManager::Draw3D()
{
	GraphicsDevice.SetCamera(_camera);

	_scene->Draw3D();
}


