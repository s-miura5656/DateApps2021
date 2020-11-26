#include "SceneManager.h"

//! �O���錾
//! �]�v�ȃC���N���[�h�����炷���߂̎�@
#include "../../Scenes/Main/MainScene.h"
#include "../../Scenes/Title/TitleScene.h"
#include"../../Scenes/Result/ResultScene.h"
#include "../ControllerManager/ContorollerManager.h"

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
	/**
	* @brief ���C�g�̏����ݒ�
	*/
	Light light;
	light.Type = Light_Directional;
	light.Direction = Vector3(0, 1, 1);
	light.Diffuse = Color(1.0f, 1.0f, 1.0f);
	light.Ambient = Color(1.0f, 1.0f, 1.0f);
	light.Specular = Color(1.0f, 1.0f, 1.0f);
	GraphicsDevice.SetLight(light);

	/**
	* @brief �J�����̏����ݒ�
	*/
	_camera_angle = 60;
	Viewport view = GraphicsDevice.GetViewport();
	_camera->SetView(Vector3(7, 15, -15), Vector3(_camera_angle, 0, 0));
	_camera->SetPerspectiveFieldOfView(40.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);
	GraphicsDevice.SetCamera(_camera);
	

	//! ��ԍŏ��ɓǂݍ��܂��V�[��
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

		if (pad->GetButtonBuffer(GamePad_Button2))
		{
			_camera_angle++;
		}

		if (pad->GetButtonBuffer(GamePad_Button3))
		{
			_camera_angle--;
		}
	}
	
	_camera->SetView(Vector3(7, 15, -15), Vector3(_camera_angle, 0, 0));*/

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


