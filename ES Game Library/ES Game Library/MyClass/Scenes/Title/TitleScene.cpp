#include"TitleScene.h"
#include"../../Data/WordsTable.h"
#include"../../Data/ModelAnimation.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include"../../Managers/AudioManager/AudioManager.h"
TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

/*
* @fn �^�C�g���̏�����
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
bool TitleScene::Initialize()
{
	_background         = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/background.png"));
	_title_logo         = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/Title.png"));
	_robot              = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/robot.png"));
	_operation_button   = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/b_button.png"));

	//! �^�C�g�����S�̃p�����[�^�[�̃Z�b�g
	title_logo_alpha    = 0.3f;
	title_logo_position = Vector3(65.0f, -200.0f, +100.0f);
	title_logo_scale    = Vector2(1.0f, 1.0f);

	//! �I�y���[�V�����{�^���摜�̃p�����[�^�[�̃Z�b�g
	operation_button_alpha = 1.0f;
	operation_button_scale = Vector2(0.9f, 0.9f);

	demo_scene_count = 0;

	button_flashing_flag   = true;
	button_push_flag       = false;
	tutorial_flag          = false;
	demo_scene_flag        = false;

	Viewport view       = GraphicsDevice.GetViewport();
	Vector3 _camera_pos = Vector3(0, 0, -10);
	Vector3 _look_pos   = Vector3(0, 0, 0);

	SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(60.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	return true;
}

int TitleScene::Update()
{
	TitleLanding();
	OperationButton();
	AudioManager::Instance().TitleBgmPlay();
	return 0;
}

/*
* @fn �^�C�g���̕`��
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
void TitleScene::Draw2D()
{

	SpriteBatch.Draw(*_background, Vector3(0.0f, 0.0f, 10000.0f));

	SpriteBatch.Draw(*_title_logo, Vector3(title_logo_position), title_logo_alpha, Vector3_Zero,
		             Vector3_Zero, Vector2(title_logo_scale));

	//! �{�^�����͂��󂯕t����t���O��true�̎��ɕ`�悷��
	if (button_push_flag)
	{
		SpriteBatch.Draw(*_operation_button, Vector3(410.0f, 340.0f, 100.0f), operation_button_alpha, Vector3_Zero,
			Vector3_Zero, Vector2(operation_button_scale));
	}

	SpriteBatch.Draw(*_robot, Vector3(0.0f, 0.0f, 100.0f));
}

void TitleScene::Draw3D()
{
	SceneCamera::Instance().SetSceneCamera();
}

//! @fn �^�C�g�����S���X�N���[��������֐�
int TitleScene::TitleLanding()
{
	auto pad = InputManager::Instance().GetGamePad(PLAYER_TAG + std::to_string(1));
	pad->Refresh();
	
	title_logo_position.y += 4.0f;

	//! �^�C�g�����S�������؂������Ƀ{�^�����͂��󂯕t����
	if (title_logo_position.y >= 125.0f)
	{
		title_logo_alpha      = 1.0f;
		title_logo_position.y = 125.0f;
		button_push_flag      = true;

		if (pad->ButtonDown(BUTTON_INFO::BUTTON_B))
		{
			SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::SELECT);
		}
		demo_scene_count++;
	}

	if(demo_scene_count >= 100)
	{ 
		//SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::DEMOMOVIE);
	}



	return 0;
}

//! @fn ����{�^���摜�̓_�ŏ���������֐�
int TitleScene::OperationButton()
{
	//! �{�^�����͂��󂯕t����t���O��true�̎��A�`�悳��Ă���摜��_�ł�����
	if (button_push_flag)
	{
		if (button_flashing_flag)
		{
			operation_button_alpha -= 0.04f;

			if (operation_button_alpha <= 0.0f)
			{
				button_flashing_flag = !button_flashing_flag;
			}
		}
		else
		{
			operation_button_alpha += 0.04f;

			if (operation_button_alpha >= 1.0f)
			{
				button_flashing_flag = !button_flashing_flag;
			}
		}
	}

	return 0;
}

