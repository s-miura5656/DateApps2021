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
	AudioManager::Instance().TitleBgmStop();

	for (auto it = _textures.rend(); it != _textures.rbegin(); --it)
	{
		delete (*it);
	}
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
	_left_arrow = ResouceManager::Instance().LordSpriteFile(_T("Select/left_arrow.png"));
	_left_arrow_dark = ResouceManager::Instance().LordSpriteFile(_T("Select/left_arrow_dark.png"));
	_right_arrow = ResouceManager::Instance().LordSpriteFile(_T("Select/right_arrow.png"));
	_right_arrow_dark = ResouceManager::Instance().LordSpriteFile(_T("Select/right_arrow_dark.png"));

	SPRITE texture;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		_textures.push_back(new PlayerTexture);

		// プレイヤーごとにテクスチャを用意する
		auto path = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(i + 1), ".png");
		texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
		_textures[i]->SetTexture(texture);
	}

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		_player_button_flag[i]   = true;
		_select_complete_flag[i] = false;
		_chara_select[i] = i;
		_chara_select_seve[i] = i;
		_player_rotation[i] = 180.0f;
		_player_rotation_flag[i] = false;
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
	AudioManager::Instance().TitleBgmPlay();

	for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
	{
		auto pad = InputManager::Instance().GetGamePad(PLAYER_TAG + std::to_string(i + 1));
		pad->Refresh();

		// カラー選択　関数作る
		if (pad->ButtonDown(BUTTON_INFO::BUTTON_B))
		{
			_select_complete_flag[i] = true;
			_player_rotation_flag[i] = true;

			//_chara_select[i] = _chara_select_seve[i];
		}

		/*if (_chara_select_seve[i] == _chara_select[i])
		{
			_select_complete_flag[i] = false;
			_player_rotation_flag[i] = false;
		}
		*/

		// 選択後モデル回転
		if (_player_rotation_flag[i])
			_player_rotation[i] += 10.0f;

		if (_player_rotation[i] >= 500.0f)
		{
			_player_rotation_flag[i] = false;
		}

		if (!_player_rotation_flag[i])
			_player_rotation[i] = 180.0f;



		if (!_select_complete_flag[i])
		{
			if (pad->Stick(STICK_INFO::LEFT_STICK).x == 0)
			{
				_left_arrow_flag[i] = true;
				_right_arrow_flag[i] = true;
			}

			if (pad->Stick(STICK_INFO::LEFT_STICK).x != 0)
			{
				// スティック倒して一定時間で次のカラーへ
				_select_count++;

				if (_select_count >= 10)
				{
					//ColorSelect(i, pad);
					//std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).x) ?
					//	_chara_select[i]--, _left_arrow_flag[i] = false : _chara_select[i]++, _right_arrow_flag[i] = false;
					if (pad->Stick(STICK_INFO::LEFT_STICK).x > 0)
					{
						_chara_select[i]++;
						_right_arrow_flag[i] = false;
					}
					else if (pad->Stick(STICK_INFO::LEFT_STICK).x < 0)
					{
						_chara_select[i]--;
						_left_arrow_flag[i] = false;
					}
					_select_count = 0;
				}
			}
		}

		if (_chara_select[i] > TEXTURE_MAX - 1)
			_chara_select[i] = 0;

		if (_chara_select[i] < 0)
			_chara_select[i] = TEXTURE_MAX - 1;

		// カラー再選択
		if (_select_complete_flag[i])
		{
			if (pad->ButtonDown(BUTTON_INFO::BUTTON_A))
			{
				_select_complete_flag[i] = false;
			}
		}

		//! プレイヤー全員の選択が終わったらフラグで判断してメインシーンへ
		if (GameStart())
		{
			if (pad->ButtonDown(BUTTON_INFO::BUTTON_B))
				SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::MAIN);
		}
	}

	return 0;

}

void SelectScene::Draw2D()
{
	SpriteBatch.Draw(*_bg_sprite, Vector3(0, 0, 10000), 1.0f);
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

		if (_left_arrow_flag[i])
			SpriteBatch.Draw(*_left_arrow, player_num + Vector3(0, 195, 9000), 1.0f);
		else
			SpriteBatch.Draw(*_left_arrow_dark, player_num + Vector3(0, 195, 9000), 1.0f);

		if (_right_arrow_flag[i])
			SpriteBatch.Draw(*_right_arrow, player_num + Vector3(0, 195, 9000), 1.0f);
		else
			SpriteBatch.Draw(*_right_arrow_dark, player_num + Vector3(0, 195, 9000), 1.0f);
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

		case PINK:
			_shader->SetTexture("m_Texture", *_textures[PINK]->GetTexture());
			break;

		case PURPLE:
			_shader->SetTexture("m_Texture", *_textures[PURPLE]->GetTexture());
			break;
		}

		_player_model->SetScale(1.0f);
		_player_model->SetPosition(Vector3(_player_position[i], 0, 0));
		_player_model->SetRotation(0, _player_rotation[i], 0);

		Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
		_shader->SetParameter("vp", vp);
		_shader->SetTechnique("UnlitAnimationModel");
		_player_model->Draw(_shader);
	}
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
	_textures[_chara_select[player_number]]->SetFlag(false);

	std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).x) ? _chara_select[player_number]-- : _chara_select[player_number]++;

	if (_chara_select[player_number] < 0)
	{
		_chara_select[player_number] = _textures.size() - 1;
	}
	else if (_chara_select[player_number] > _textures.size() - 1)
	{
		_chara_select[player_number] = 0;
	}

	while (true)
	{
		if (_textures[_chara_select[player_number]]->IsFlag())
		{
			std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).x) ? _chara_select[player_number]-- : _chara_select[player_number]++;
			
			if (_chara_select[player_number] < 0)
			{
				_chara_select[player_number] = _textures.size() - 1;
			}
			else if (_chara_select[player_number] > _textures.size() - 1)
			{
				_chara_select[player_number] = 0;
			}
			continue;
		}
		else
		{
			break;
		}
	}

	_textures[_chara_select[player_number]]->SetFlag(true);
	_left_arrow_flag[player_number] = false;
}
