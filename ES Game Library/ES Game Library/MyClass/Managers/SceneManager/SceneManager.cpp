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
	
	SceneLight::Instance().SetLightParametor(light);
	SceneLight::Instance().SetSceneLight();

	/**
	* @brief �J�����̏����ݒ�
	*/
	Viewport view = GraphicsDevice.GetViewport();
	Vector3 _camera_pos = Vector3(7, 600, -400);
	Vector3 _look_pos   = Vector3(7, 0, -5.5f);

	SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(1.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

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
	SceneCamera::Instance().SetSceneCamera();

	_scene->Draw3D();
}


