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

	siyakaku = 1.0;
	view = GraphicsDevice.GetViewport();
	_camera_pos = Vector3(7, 482, -400);
	_look_pos = Vector3(7, 0, -4.6);

	SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(0.93, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);
	return true;
}

int SceneManager::Update()
{
	_scene->Update();
	/**
* @brief �J�����̏����ݒ�
*/

	KeyboardState key = Keyboard->GetState();
//�p�[�X�����p
	if (key.IsKeyDown(Keys_A)) {
		siyakaku+= 0.01;
	}
	if (key.IsKeyDown(Keys_Z)) {
		siyakaku -= 0.01;
	}
	if (key.IsKeyDown(Keys_S)) {
		_camera_pos.y += 2;
	}
	if (key.IsKeyDown(Keys_X)) {
		_camera_pos.y -= 2;
	}
	if (key.IsKeyDown(Keys_D)) {
		_look_pos.z += 0.1;
	}
	if (key.IsKeyDown(Keys_C)) {
		_look_pos.z -= 0.1;
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


