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
	_player_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		// プレイヤーごとにテクスチャを用意する
		auto path        = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(i +1), ".png");
		SPRITE texture   = ResouceManager::Instance().LordSpriteFile(path.c_str());
		_texture[i]      = texture;
		_chara_select[i] = 0;
		_player_button_flag[i] = true;
	}

	_player_position[0] = -3;
	_player_position[1] = -1;
	_player_position[2] = 1;
	_player_position[3] = 3;

	_select_complete_flag = false;


	Viewport view            = GraphicsDevice.GetViewport();
	Vector3 _camera_pos      = Vector3(0, 0, -5);
	Vector3 _camera_rotation = Vector3(0, 0, 0);

	SceneCamera::Instance().SetView(_camera_pos, _camera_rotation);
	SceneCamera::Instance().SetPerspectiveFieldOfView(57, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	Light light;
	light.Type      = Light_Directional;
	light.Direction = Vector3(0, -1, 1);
	light.Diffuse   = Color(1.0f, 1.0f, 1.0f);
	light.Ambient   = Color(1.0f, 1.0f, 1.0f);
	light.Specular  = Color(1.0f, 1.0f, 1.0f);

	SceneLight::Instance().SetLightParametor(light);
	SceneLight::Instance().SetSceneLight();

	return true;
}

int SelectScene::Update()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
	{
		auto pad = InputManager::Instance().GetGamePad(PLAYER_TAG + std::to_string(i + 1));
		pad->Refresh();

		//! プレイヤー全員の選択が終わったらフラグで判断してメインシーンへ
		//if()
		{
			//_select_complete_flag = true;
		}
		if (pad->ButtonDown(BUTTON_INFO::BUTTON_B))
		{
			_player_button_flag[i] = true;
		}
		//if (pad->Stick(i + 1).x > 0)
		//{
		//	_chara_select[i]++;
		//}
		//if (pad->Stick(i + 1).x < 0)
		//{
		//	_chara_select[i]--;
		//}
		//if (_chara_select[i] >= 4)
		//{
		//	_chara_select[i] = 0;
		//}
	}
	if (_player_button_flag[0] && _player_button_flag[1] && _player_button_flag[2] && _player_button_flag[3])
	{
		SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::MAIN);
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
		if(!_player_button_flag[i])
		SpriteBatch.Draw(*_button_ready, player_num + Vector3(0, 400, 9000), 1.0f);
		else
		SpriteBatch.Draw(*_button_go, player_num + Vector3(0, 400, 9000), 1.0f);
	}
}

void SelectScene::Draw3D()
{

	Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
	SceneCamera::Instance().SetSceneCamera();

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		/*switch (_chara_select[i])
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

		default:
			break;
		}*/
		_shader->SetTexture("m_Texture", *_texture[i]);
		_shader->SetParameter("vp", vp);
		_shader->SetParameter("model_ambient", Color(1.f, 1.f, 1.f));
		_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);
		_shader->SetParameter("eye_pos", SceneCamera::Instance().GetCamera().GetPosition());

		_player_model->SetScale(1.0f);
		_player_model->SetPosition(Vector3(_player_position[i],0,0));
		_player_model->SetRotation(0,180,0);
		_player_model->Draw(_shader);
	}
}