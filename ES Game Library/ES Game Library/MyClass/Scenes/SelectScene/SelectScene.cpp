#include "SelectScene.h"
#include "../../Managers/SceneManager/SceneManager.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Managers/InputManager/InputManager.h"
#include "../../Data/IData.h"
#include"../../Managers/AudioManager/AudioManager.h"
SelectScene::SelectScene()
{

}

SelectScene::~SelectScene()
{

	//for (auto it = _textures.rend(); it != _textures.rbegin(); --it)
	//{
	//	delete (*it);
	//}
}

bool SelectScene::Initialize()
{
	_bg_sprite = ResouceManager::Instance().LordSpriteFile(_T("Select/BG.png"));
	_banner = ResouceManager::Instance().LordSpriteFile(_T("Select/character.png"));
	_button_ready = ResouceManager::Instance().LordSpriteFile(_T("Select/ready_button.png"));
	_button_go = ResouceManager::Instance().LordSpriteFile(_T("Select/ok_button.png"));
	_player_model = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	_left_arrow = ResouceManager::Instance().LordSpriteFile(_T("Select/arrow.png"));
	_left_arrow_dark = ResouceManager::Instance().LordSpriteFile(_T("Select/arrow.png"));
	_right_arrow = ResouceManager::Instance().LordSpriteFile(_T("Select/arrow.png"));
	_right_arrow_dark = ResouceManager::Instance().LordSpriteFile(_T("Select/arrow.png"));
	_dark_screen = ResouceManager::Instance().LordSpriteFile(_T("Select/dark_screen.png"));
	_ready_to_fight = ResouceManager::Instance().LordSpriteFile(_T("Select/ready_to_fight.png"));
	SPRITE texture;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		_textures.push_back(new PlayerTexture);

		// プレイヤーごとにテクスチャを用意する
		auto path = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(i + 1), ".png");
		texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
		_textures[i]->SetTexture(texture);
		_textures[i]->SetFlag(false);
	}

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		_player_button_flag[i] = true;
		_select_complete_flag[i] = false;
		_chara_select[i] = i;
		_textures[i]->SetFlag(true);
		_player_rotation[i] = 180.0f;
		_player_rotation_flag[i] = false;
		_banner_color[i] = i;
		_old_x_stick[i] = 0.0f;
		_left_arrow_flag[i] = false;
		_right_arrow_flag[i] = false;
	}

	_confirming_flag = false;
	_game_start_flag = false;

	_player_position[0] = -3.3;
	_player_position[1] = -1.1;
	_player_position[2] = 1.1;
	_player_position[3] = 3.3;

	Light light;
	light.Type = Light_Directional;
	light.Direction = Vector3(0, -1, 1);
	light.Position = Vector3_Zero;
	light.Diffuse = Color(1.0f, 1.0f, 1.0f);
	light.Ambient = Color(1.0f, 1.0f, 1.0f);
	light.Specular = Color(1.0f, 1.0f, 1.0f);

	SceneLight::Instance().SetLightParametor(light);
	SceneLight::Instance().SetSceneLight();

	Viewport view = GraphicsDevice.GetViewport();
	Vector3 _camera_pos = Vector3(0, 0, -5);
	Vector3 _camera_rotation = Vector3(0, 0, 0);

	SceneCamera::Instance().SetView(_camera_pos, _camera_rotation);
	SceneCamera::Instance().SetPerspectiveFieldOfView(57, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	for (int i = 0; i < 5; i++)
	{
		_player_model->SetTrackPosition(i, 0);
		_player_model->SetTrackEnable(i, false);
	}

	_player_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");
	_player_model->SetTrackEnable(0, TRUE);

	return true;
}

int SelectScene::Update()
{
	AudioManager::Instance().TitleBgmPlay();

	//_player_model->SetTrackEnable(0, false);

	for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
	{
		auto pad = InputManager::Instance().GetGamePad(PLAYER_TAG + std::to_string(i + 1));
		pad->Refresh();

		//! カラー選択　関数作る
		if (pad->Button(BUTTON_INFO::BUTTON_B))
		{
			bool animflag = false;
			for (int j = 0; j < PLAYER_COUNT_MAX; j++)
			{
				if (i == j)
					continue;
				if (_select_complete_flag[j])
					animflag = true;
			}
			if (!_select_complete_flag[i])
			{
				AudioManager::Instance().SelectPlay();
				if (!animflag)
					_jumpanimation_count = 0;
			}
			_select_complete_flag[i] = true;
			_player_rotation_flag[i] = true;
		}

		if (_select_complete_flag[i])
		{
			if (pad->Stick(STICK_INFO::LEFT_STICK).x != 0)
			{
				_player_rotation[i] += -pad->Stick(STICK_INFO::LEFT_STICK).x / 10000;
			}
		}
		if (_player_rotation[i] > 360)
		{
			_player_rotation[i] = 0;
		}
		if (_player_rotation[i] < 0)
		{
			_player_rotation[i] = 360;
		}
		if (!_select_complete_flag[i])
		{
			//! スティック入力に応じて矢印の描画
			if (pad->Stick(STICK_INFO::LEFT_STICK).x == 0)
			{
				_left_arrow_flag[i] = true;
				_right_arrow_flag[i] = true;
			}

			if (pad->Stick(STICK_INFO::LEFT_STICK).x != 0)
			{
				auto a = std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).x);

				const auto STICK_DELTA = pad->Stick(STICK_INFO::LEFT_STICK).x - _old_x_stick[i];
				if (STICK_DELTA >= Axis_Max / 8 && pad->Stick(STICK_INFO::LEFT_STICK).x >= Axis_Max * 0.90f)
				{
					_textures[_chara_select[i]]->SetFlag(false);
					_banner_color[i] = ColorSelect2(i, +1);

					_right_arrow_flag[i] = false;
					_left_arrow_flag[i] = true;
				}

				else if (STICK_DELTA <= Axis_Min / 8 && pad->Stick(STICK_INFO::LEFT_STICK).x <= Axis_Min * 0.90f)
				{
					_textures[_chara_select[i]]->SetFlag(false);
					_banner_color[i] = ColorSelect2(i, -1);

					_left_arrow_flag[i] = false;
					_right_arrow_flag[i] = true;
				}
			}
		}

		_old_x_stick[i] = pad->Stick(STICK_INFO::LEFT_STICK).x;

		//! カラー再選択
		if (_select_complete_flag[i])
		{
			_left_arrow_flag[i] = true;
			_right_arrow_flag[i] = true;
			if (pad->Button(BUTTON_INFO::BUTTON_A))
			{
				AudioManager::Instance().CancelPlay();
				_player_rotation[i] = 180;
				_select_complete_flag[i] = false;
			}
		}

		//! プレイヤー全員の選択が終わったらフラグで判断してメインシーンへ
		if (_select_complete_flag[0] && _select_complete_flag[1] && _select_complete_flag[2] && _select_complete_flag[3])
		{
			for (int i = 0; i < PLAYER_COUNT_MAX; i++)
			{
				std::string tag = PLAYER_TAG + to_string(i + 1);
				SceneManager::Instance().SetPlayerTexture(tag, _chara_select[i]);
			}

			_confirming_flag = true;
		}

		if (_confirming_flag)
		{
			if (pad->Button(BUTTON_INFO::BUTTON_B))
			{
				_game_start_flag = true;
				AudioManager::Instance().SelectPlay();
			}

			if (pad->Button(BUTTON_INFO::BUTTON_A))
			{
				_confirming_flag = false;
				AudioManager::Instance().CancelPlay();
			}

		}

		if (_game_start_flag)
		{
			if (pad->Button(BUTTON_INFO::BUTTON_B))
			{
				SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::MAIN);
				AudioManager::Instance().SelectPlay();
				AudioManager::Instance().TitleBgmStop();
			}
		}
	}

	//!デバッグ
	KeyboardState key = Keyboard->GetState();
	if (key.IsKeyDown(Keys_Enter))
	{
		for (int i = 0; i < PLAYER_COUNT_MAX; i++)
		{
			std::string tag = PLAYER_TAG + to_string(i + 1);
			SceneManager::Instance().SetPlayerTexture(tag, _chara_select[i]);
		}
		//SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::MAIN);
		_confirming_flag = true;
	}

	return 0;

}

void SelectScene::Draw2D()
{
	SpriteBatch.Draw(*_bg_sprite, Vector3(0, 0, 10000), 1.0f);
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		auto player_num = GraphicsDevice.WorldToScreen(Vector3(_player_position[i], 0, 0));
		player_num.x += 60 + 300 * i;
		SpriteBatch.Draw(*_banner, player_num + Vector3(0, 85, 9000), RectWH(256 * _chara_select[i], 0, 256, 512));
		if (!_select_complete_flag[i])
		{
			SpriteBatch.Draw(*_button_ready, player_num + Vector3(1, 420, 9000), 1.0f);
		}
		else
		{
			SpriteBatch.Draw(*_button_go, player_num + Vector3(1, 420, 9000), 1.0f);
		}

		if (_left_arrow_flag[i])
			SpriteBatch.Draw(*_left_arrow, player_num + Vector3(0, 50, 9000), RectWH(0, 0, 256, 512));
		else
			SpriteBatch.Draw(*_left_arrow_dark, player_num + Vector3(0, 50, 9000), RectWH(256, 0, 256, 512));

		if (_right_arrow_flag[i])
			SpriteBatch.Draw(*_right_arrow, player_num + Vector3(1, 50, 9000), RectWH(256 * 2, 0, 256, 512));
		else
			SpriteBatch.Draw(*_right_arrow_dark, player_num + Vector3(1, 50, 9000), RectWH(256 * 3, 0, 256, 512));

		if (_confirming_flag)
		{
			SpriteBatch.Draw(*_dark_screen, Vector3(0, 0, 0), 0.2f);
			SpriteBatch.Draw(*_ready_to_fight, Vector3(0, 0, 0));
		}
	}
}

void SelectScene::Draw3D()
{

	SceneCamera::Instance().SetSceneCamera();

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		switch (_chara_select[i])
		{
		case RED:
			_shader->SetTexture("m_Texture", *_textures[RED]->GetTexture());
			break;

		case BLUE:
			_shader->SetTexture("m_Texture", *_textures[BLUE]->GetTexture());
			break;

		case GREEN:
			_shader->SetTexture("m_Texture", *_textures[GREEN]->GetTexture());
			break;

		case YELLOW:
			_shader->SetTexture("m_Texture", *_textures[YELLOW]->GetTexture());
			break;

		case LIGHTBLUE:
			_shader->SetTexture("m_Texture", *_textures[LIGHTBLUE]->GetTexture());
			break;

		case ORANGE:
			_shader->SetTexture("m_Texture", *_textures[ORANGE]->GetTexture());
			break;

		case LIGHTGREEN:
			_shader->SetTexture("m_Texture", *_textures[LIGHTGREEN]->GetTexture());
			break;

		case PURPLE:
			_shader->SetTexture("m_Texture", *_textures[PURPLE]->GetTexture());
			break;
		}

		_player_model->SetScale(1.0f);
		_player_model->SetPosition(Vector3(_player_position[i], -0.1, 0));
		_player_model->SetRotation(0, _player_rotation[i], 0);

		Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
		_shader->SetParameter("vp", vp);
		_shader->SetTechnique("UnlitAnimationModel");

		if (!_confirming_flag)
		{
			if (!_select_complete_flag[i])
			{

				_player_model->SetTrackEnable(0, TRUE);
				_player_model->SetTrackEnable(5, false);
				_player_model->SetTrackPosition(0, _animation_count);
			}
			else
			{

				_player_model->SetTrackEnable(0, false);
				_player_model->SetTrackEnable(5, TRUE);
				if (_jumpanimation_count >= 1.3f)
					_jumpanimation_count = 0;
				_player_model->SetTrackPosition(5, _jumpanimation_count);
			}
		}
		_player_model->Draw(_shader);
	}
	_animation_count += GameTimer.GetElapsedSecond();
	_jumpanimation_count += GameTimer.GetElapsedSecond();
}

bool SelectScene::GameStart()
{
	// 全プレイヤーの選択が終わっているか判断する関数
	for (auto start_flag : _select_complete_flag)
	{
		if (start_flag)
			continue;
		else
			return false;
	}

	return true;
}

void SelectScene::ColorSelect(int player_number, BaseInput* pad)
{
	while (true)
	{
		if (_chara_select[player_number] < 0)
			_chara_select[player_number] = _textures.size() - 1;
		else if (_chara_select[player_number] > _textures.size() - 1)
			_chara_select[player_number] = 0;

		if (_textures[_chara_select[player_number]]->IsFlag())
		{
			std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).x) ? _chara_select[player_number]-- : _chara_select[player_number]++;
			continue;
		}
		else
		{
			_textures[_chara_select[player_number]]->SetFlag(true);

			break;
		}
	}
}

int SelectScene::ColorSelect2(int player_number, int direction)
{
	int select_color = _chara_select[player_number] + direction;
	while (true)
	{
		if (select_color < 0)
			select_color = _textures.size() - 1;
		else if (select_color >= _textures.size())
			select_color = 0;

		if (!_textures[select_color]->IsFlag())
		{
			_chara_select[player_number] = select_color;
			_textures[select_color]->SetFlag(true);
			break;
		}

		select_color += direction;
	}

	return select_color;
}

