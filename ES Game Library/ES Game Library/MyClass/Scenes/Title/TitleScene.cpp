#include"TitleScene.h"
#include"../../Data/WordsTable.h"
#include"../../Data/ModelAnimation.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

/*
* @fn タイトルの初期化
* @param　なし
* @return　なし
*/
bool TitleScene::Initialize()
{
	_background = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/background.png"));
	_title      = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/Title.png"));
	_robot      = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/robot.png"));
	_b_button   = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/b_button.png"));
	_tutorial   = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/tutorial.png"));

	button_alpha = 1.0f;
	alpha_flag   = true;
	button_flag  = false;

	tutorial_flag = false;

	title_pos = Vector3(65.0f, -200.0f, +100.0f);

	title_scale  = Vector2(1.0f, 1.0f);
	button_scale = Vector2(0.9f, 0.9f);
	
	ControllerManager::Instance().CreateGamePad(PLAYER_TAG + std::to_string(1));
	ControllerManager::Instance().SetGamePadMaxCount(PLAYER_COUNT_MAX);

	Viewport view = GraphicsDevice.GetViewport();
	Vector3 _camera_pos = Vector3(0, 0, -10);
	Vector3 _look_pos = Vector3(0, 0, 0);

	SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(60.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	return true;
}
/*
* @fn タイトルの更新
* @param　なし
* @return　なし
*/
int TitleScene::Update()
{
	auto pad = ControllerManager::Instance().GetController(PLAYER_TAG + std::to_string(1));
	pad->GamePadRefresh();
	
	title_pos.y += 4.0f;

	if (title_pos.y >= 125.0f)
	{
		title_pos.y = 125.0f;
		button_flag = true;

		if (!tutorial_flag)
		{
			if (pad->GetButtonBuffer(GamePad_Button2))
			{
				tutorial_flag = true;
			}
		}
		else
		{
			if (pad->GetButtonBuffer(GamePad_Button2)) 
			{
				SceneManager::Instance().ChangeScene(SceneManager::MAIN);
			}
		}
	}

	title_scale += Vector2(0.0075f, 0.0075f);

	if (title_scale.x > 1.0f)
	{
		title_scale = Vector2(1.0f, 1.0f);
	}

	if (button_flag)
	{
		if (alpha_flag)
		{
			button_alpha -= 0.04f;

			if (button_alpha <= 0.0f)
			{

				alpha_flag = !alpha_flag;
			}
		}
		else
		{
			button_alpha += 0.04f;

			if (button_alpha >= 1.0f)
			{
				alpha_flag = !alpha_flag;
			}
		}
	}

	return 0;
}

/*
* @fn タイトルの描画
* @param　なし
* @return　なし
*/
void TitleScene::Draw2D()
{
	if (!tutorial_flag)
	{
		SpriteBatch.Draw(*_background, Vector3(0.0f, 0.0f, 10000.0f));

		SpriteBatch.Draw(*_title, Vector3(title_pos), 1.0f, Vector3(0, 0, 0),
			Vector3(0, 0, 0), Vector2(title_scale));
		if (button_flag)
		{
			SpriteBatch.Draw(*_b_button, Vector3(410.0f, 340.0f, 100.0f), button_alpha, Vector3(0, 0, 0),
				Vector3(0, 0, 0), Vector2(button_scale));
		}
		SpriteBatch.Draw(*_robot, Vector3(0.0f, 0.0f, 100.0f));
	}

	if (tutorial_flag)
		SpriteBatch.Draw(*_tutorial, Vector3(0.0f, 0.0f, 10000.0f));
}

void TitleScene::Draw3D()
{
	SceneCamera::Instance().SetSceneCamera();
}

