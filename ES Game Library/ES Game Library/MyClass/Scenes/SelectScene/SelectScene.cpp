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
	_player_model = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	_shader       = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	_player_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		// �v���C���[���ƂɃe�N�X�`����p�ӂ���
		auto path        = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(i +1), ".png");
		SPRITE texture   = ResouceManager::Instance().LordSpriteFile(path.c_str());
		_texture[i]      = texture;
		_chara_select[i] = 0;

		_player_position[0] = -3;
		_player_position[1] = -1;
		_player_position[2] =  1;
		_player_position[3] =  3;
	}

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

		// �v���C���[�S���̑I�����I�������t���O�Ŕ��f���ă��C���V�[����
		//if()
		{
			_select_complete_flag = true;
		}

		if (_select_complete_flag)
		{
			if (pad->ButtonDown(GamePad_Button2))
			{
				SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::MAIN);
			}
		}
	
		if (pad->Stick(i + 1).x > 0)
		{
			_chara_select[i]++;
		}
		if (pad->Stick(i + 1).x < 0)
		{
			_chara_select[i]--;
		}
		if (_chara_select[i] >= 4)
		{
			_chara_select[i] = 0;
		}
	}

	return 0;
}

void SelectScene::Draw2D()
{
}

void SelectScene::Draw3D()
{

	Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
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

		default:
			break;
		}
		_shader->SetParameter("vp", vp);
		_shader->SetParameter("model_ambient", Color(1.f, 1.f, 1.f));
		_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);
		_shader->SetParameter("eye_pos", SceneCamera::Instance().GetCamera().GetPosition());

		_player_model->SetScale(1.0f);
		_player_model->SetPosition(Vector3(_player_position[i],0,0));
		_player_model->SetRotation(Vector3_Zero);
		_player_model->Draw(_shader);
	}
}