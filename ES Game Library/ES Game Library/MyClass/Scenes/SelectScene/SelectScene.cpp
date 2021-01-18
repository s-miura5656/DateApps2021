#include "SelectScene.h"
#include "../../Managers/SceneManager/SceneManager.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Managers/InputManager/InputManager.h"
#include "../../Data/IData.h"

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

bool SelectScene::Initialize()
{
	_bg_sprite = ResouceManager::Instance().LordSpriteFile(_T("Select/screen.png"));
	_banner = ResouceManager::Instance().LordSpriteFile(_T("Select/character_02.png"));
	_button_ready = ResouceManager::Instance().LordSpriteFile(_T("Select/button_redy02.png"));
	_button_go = ResouceManager::Instance().LordSpriteFile(_T("Select/button_go02.png"));
	_player_model = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	_shader       = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));

	_chara_frame = ResouceManager::Instance().LordSpriteFile(_T("Select/character_frame.png"));
	_button_frame = ResouceManager::Instance().LordSpriteFile(_T("Select/button_frame.png"));

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		// プレイヤーごとにテクスチャを用意する
		auto path = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(i + 1), ".png");
		SPRITE texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
		_texture[i] = texture;
	}

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		_player_button_flag[i] = true;
		_select_complete_flag[i] = false;
		_chara_select[i] = i;
	}

	_player_position[0] = -3;
	_player_position[1] = -0.8;
	_player_position[2] = 1.4;
	_player_position[3] = 3.6;

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

	_player_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");
	return true;
}

int SelectScene::Update()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
	{
		auto pad = InputManager::Instance().GetGamePad(PLAYER_TAG + std::to_string(i + 1));
		pad->Refresh();

		if (!_select_complete_flag[i])
		{
			// カラー選択　関数作る
			if (pad->ButtonDown(BUTTON_INFO::BUTTON_B))
			{
				_select_complete_flag[i] = true;
			}

			if (pad->Stick(STICK_INFO::LEFT_STICK).x == 0)
			{

			}

			if (pad->Stick(STICK_INFO::LEFT_STICK).x != 0)
			{
				// スティック倒して一定時間で次のカラーへ
				_select_count++;

				if (_select_count >= 10)
				{
					std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).x) ?
						_chara_select[i]-- : _chara_select[i]++;

					_select_count = 0;
				}

				// プレイヤー同士のカラー被り避け
				for (int j = 0; j < PLAYER_COUNT_MAX; ++j)
				{
					if (i == j)
					{
						continue;
					}

					if (_chara_select[i] == _chara_select[j])
					{
						std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).x) ? _chara_select[i]-- : _chara_select[i]++;
					}
				}
			}

			if (_chara_select[i] > TEXTURE_MAX - 1)
			{
				_chara_select[i] = 0;
			}
			else if (_chara_select[i] < 0)
			{
				_chara_select[i] = TEXTURE_MAX - 1;
			}
		}

		// カラー再選択
		if (_select_complete_flag[i])
		{
			if (pad->ButtonDown(BUTTON_INFO::BUTTON_A))
			{
				_select_complete_flag[i] = false;
			}
		}

		//! プレイヤー全員の選択が終わったらフラグで判断してメインシーンへ
		if (_select_complete_flag[0] && _select_complete_flag[1] && _select_complete_flag[2] && _select_complete_flag[3])
		{
			_game_start_flag = true;
		}
		if (_game_start_flag)
		{
			if (pad->ButtonDown(BUTTON_INFO::BUTTON_B))
				SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::MAIN);
		}
	}

	return 0;

}

void SelectScene::Draw2D()
{
	SpriteBatch.Draw(*_bg_sprite, Vector3(0, 0, 10000));
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		auto player_num = GraphicsDevice.WorldToScreen(Vector3(_player_position[i], 0, 0));
		player_num.x += 100 + 300 * i;
		SpriteBatch.Draw(*_banner, player_num + Vector3(0, 150, 9000), 1.0f);
		if (!_select_complete_flag[i])
		{
			SpriteBatch.Draw(*_chara_frame, player_num + Vector3(0, 195, 9000), 1.0f);
			SpriteBatch.Draw(*_button_ready, player_num + Vector3(0, 400, 9000), 1.0f);
		}
		else
		{
			SpriteBatch.Draw(*_button_frame, player_num + Vector3(0, 400, 9000), 1.0f);
			SpriteBatch.Draw(*_button_go, player_num + Vector3(0, 400, 9000), 1.0f);
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
			_shader->SetTexture("m_Texture", *_texture[RED]);
			break;

		case BLUE:
			_shader->SetTexture("m_Texture", *_texture[BLUE]);
			break;

		case GREEN:
			_shader->SetTexture("m_Texture", *_texture[GREEN]);
			break;

		case YELLOW:
			_shader->SetTexture("m_Texture", *_texture[YELLOW]);
			break;

		case LIGHTBLUE:
			_shader->SetTexture("m_Texture", *_texture[LIGHTBLUE]);
			break;

		case PINK:
			_shader->SetTexture("m_Texture", *_texture[PINK]);
			break;

		case PURPLE:
			_shader->SetTexture("m_Texture", *_texture[PURPLE]);
			break;
		}

		_player_model->SetScale(1.0f);
		_player_model->SetPosition(Vector3(_player_position[i], 0, 0));
		_player_model->SetRotation(0, 180, 0);

		Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
		_shader->SetParameter("vp", vp);
		_shader->SetTechnique("UnlitAnimationModel");
		_player_model->Draw(_shader);
	}
}