#include "DemoMovieScene.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"
#include "../../Managers/SceneManager/SceneManager.h"
#include "../../Scenes/Title/TitleScene.h"

DemoMovieScene::DemoMovieScene()
{
}

DemoMovieScene::~DemoMovieScene()
{
}

bool DemoMovieScene::Initialize()
{
	_operation_button = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/b_button.png"));

	MediaManager.Attach(GraphicsDevice);
	_demo_movie = ResouceManager::Instance().LordMediaFile(_T("DemoMovie/movie.png"));
	

	//! オペレーションボタン画像のパラメーターのセット
	operation_button_alpha = 1.0f;
	operation_button_scale = Vector2(0.9f, 0.9f);
	button_flashing_flag = true;

	movie_replay_flag = false;

	replay_count = 0;

	return true;
}

int DemoMovieScene::Update()
{
	if(movie_replay_flag == false)
	_demo_movie->Play();

	auto pad = ControllerManager::Instance().GetController(PLAYER_TAG + std::to_string(1));
	pad->GamePadRefresh();

	if (pad->GetButtonBuffer(GamePad_Button2))
	{
		// ここでタイトルシーンに遷移
		SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::TITLE);
		movie_replay_flag = true;
	}

	if (movie_replay_flag == true)
	{
		_demo_movie->Replay();
	}


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

	return 0;
}

void DemoMovieScene::Draw2D()
{
	SpriteBatch.Draw(*_demo_movie, Vector3(0, 0, 10000), 1.0f, Vector3(0, 0, 0), Vector3(0, 0, 0),
		             Vector2(1.0f, 1.0f));
	SpriteBatch.Draw(*_operation_button, Vector3(410.0f, 340.0f, 100.0f), operation_button_alpha, Vector3_Zero,
		             Vector3_Zero, Vector2(operation_button_scale));
}
