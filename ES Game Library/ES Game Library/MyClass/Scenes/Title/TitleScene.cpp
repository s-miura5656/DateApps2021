#include"TitleScene.h"
#include"../../Data/WordsTable.h"
#include"../../Data/ModelAnimation.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include"../../Managers/AudioManager/AudioManager.h"
#include"../../Managers/AudioManager/AudioManager.h"
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
	_background         = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/background.png"));
	_title_logo         = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/Title.png"));
	_robot              = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/robot.png"));
	_operation_button   = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/b_button.png"));

	MediaManager.Attach(GraphicsDevice);
	_demo_movie = ResouceManager::Instance().LordMediaFile(_T("TitleSprite/BG.wmv"));


	//! タイトルロゴのパラメーターのセット
	_title_logo_alpha    = 0.3f;
	_title_logo_position = Vector3(0.0f, -200.0f, +100.0f);
	_title_logo_scale    = Vector2(1.0f, 1.0f);

	//! オペレーションボタン画像のパラメーターのセット
	_operation_button_alpha = 1.0f;
	_operation_button_scale = Vector2(0.9f, 0.9f);

	_demo_scene_count = 0;
	_play_count = 0;
	_movie_flag = false;


	_button_flashing_flag   = true;
	_button_push_flag       = false;
	_tutorial_flag          = false;
	_demo_move_flag        = false;

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
* @fn タイトルの描画
* @param　なし
* @return　なし
*/
void TitleScene::Draw2D()
{
	if (!_demo_move_flag)
	{
		SpriteBatch.Draw(*_background, Vector3(0.0f, 0.0f, 10000.0f));

		SpriteBatch.Draw(*_title_logo, Vector3(_title_logo_position), _title_logo_alpha, Vector3_Zero,
			Vector3_Zero, Vector2(_title_logo_scale));

		//SpriteBatch.Draw(*_robot, Vector3(0.0f, 0.0f, 9000.0f));
	}

	//! ボタン入力を受け付けるフラグがtrueの時に描画する
	if (_button_push_flag)
	{
		SpriteBatch.Draw(*_operation_button, Vector3(410.0f, 540.0f, 7000.0f), _operation_button_alpha, Vector3_Zero,
			Vector3_Zero, Vector2(_operation_button_scale));
	}

	if(_demo_move_flag)
	SpriteBatch.Draw(*_demo_movie, Vector3(0, 0, 8000), 1.0f, Vector3(0, 0, 0), Vector3(0, 0, 0),Vector2(1.0f, 1.0f));
}

void TitleScene::Draw3D()
{
	SceneCamera::Instance().SetSceneCamera();
}

//! @fn タイトルロゴをスクロールさせる関数
int TitleScene::TitleLanding()
{
	auto pad = InputManager::Instance().GetGamePad(PLAYER_TAG + std::to_string(1));
	pad->Refresh();
	
	if (!_demo_move_flag)
	{
		_title_logo_position.y += 4.0f;

		//! タイトルロゴが落ち切った時にボタン入力を受け付ける
		if (_title_logo_position.y >= 0.0f)
		{
			_title_logo_alpha = 1.0f;
			_title_logo_position.y = 0.0f;
			_button_push_flag = true;

			if (pad->Button(BUTTON_INFO::BUTTON_B))
			{
				AudioManager::Instance().SelectPlay();
				SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::SELECT);
			}
			_demo_scene_count++;
		}
	}
	if (_demo_scene_count >= 200)
	{
		_demo_move_flag = true;
		_demo_scene_count = 0;
	}

	if(_demo_move_flag)
		DemoMove();


	return 0;
}

//! @fn 操作ボタン画像の点滅処理をする関数
int TitleScene::OperationButton()
{
	//! ボタン入力を受け付けるフラグがtrueの時、描画されている画像を点滅させる
	if (_button_push_flag)
	{
		if (_button_flashing_flag)
		{
			_operation_button_alpha -= 0.04f;

			if (_operation_button_alpha <= 0.0f)
			{
				_button_flashing_flag = !_button_flashing_flag;
			}
		}
		else
		{
			_operation_button_alpha += 0.04f;

			if (_operation_button_alpha >= 1.0f)
			{
				_button_flashing_flag = !_button_flashing_flag;
			}
		}
	}

	return 0;
}

void TitleScene::DemoMove()
{
	auto pad = InputManager::Instance().GetGamePad(PLAYER_TAG + std::to_string(1));
	
	if (_play_count > 0) {
		if(!_movie_flag) {
			_demo_movie->Replay();
			_movie_flag = true;
		}
	}
	else
	    _demo_movie->Play();
	
	if (pad->ButtonDown(BUTTON_INFO::BUTTON_B))
	{
		AudioManager::Instance().SelectPlay();
		_title_logo_position = Vector3(0.0f, -200.0f, 100.0f);
		_title_logo_alpha = 0.3f;
		_demo_move_flag = false;
		_demo_movie->Pause();
		_play_count += 1;
		_movie_flag = false;
	}

}

