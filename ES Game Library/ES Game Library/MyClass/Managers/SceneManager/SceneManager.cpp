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
	delete _result_data;
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
	light.Direction = Vector3(1, -1, 1);
	light.Diffuse = Color(1.0f, 1.0f, 1.0f);
	light.Ambient = Color(1.0f, 1.0f, 1.0f);
	light.Specular = Color(1.0f, 1.0f, 1.0f);
	
	SceneLight::Instance().SetLightParametor(light);
	SceneLight::Instance().SetSceneLight();

	_result_data = new ResultData();

	_viewing_angle = 60;
	view = GraphicsDevice.GetViewport();
	_camera_pos = Vector3(7, 11, -11.6);
	_look_pos = Vector3(65.2, 0, 0);
	//SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);
	SceneCamera::Instance().SetView(Vector3(7, 11, -11.6), Vector3(65.2, 0, 0));
	SceneCamera::Instance().SetPerspectiveFieldOfView(57, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);
	return true;
}

int SceneManager::Update()
{
	_scene->Update();
	/**
* @brief �J�����̏����ݒ�
*/

	KeyboardState key = Keyboard->GetState();

	//SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);

//�p�[�X�����p
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
	_scene->DrawAlpha3D();
}

void SceneManager::SetResultData(int ranknum[PLAYER_COUNT_MAX], int points[PLAYER_COUNT_MAX]) {
	
	for (int number = 0 ; number < PLAYER_COUNT_MAX;number++)
	{
		_result_data->ranknum[number] = ranknum[number];
		_result_data->points[number] = points[number];
	}
}

