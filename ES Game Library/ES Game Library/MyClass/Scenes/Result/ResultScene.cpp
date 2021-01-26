#include"ResultScene.h"
#include"../../Data/WordsTable.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include "../../Managers/InputManager/InputManager.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Data/IData.h"
#include "../../Managers/AudioManager/AudioManager.h"
ResultScene::ResultScene()
{

}

ResultScene::~ResultScene()
{
	SceneManager::Instance().ClearPlayerTexture();
}

/*
* @fn ���U���g�̏�����
*/
bool ResultScene::Initialize()
{
	ArrivalCount();

	//! file
	_player_rank_num     = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/number.png"));
	_background		     = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/ground.png"));
	_player_first_ground = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/player_grond.png"));
	_robot_win           = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/robot_win.png"));
	_robot_fece          = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/result_robo.png"));
	_light               = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/light.png"));
	_totitle	         = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/button.png"));
	_shader  	         = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	_player_model        = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	_score_sprite        = ResouceManager::Instance().LordSpriteFile(_T("NumberSprite/namber.png"));
	//!���{UI�����ݒ�
	std::string first_name = PLAYER_TAG + to_string(GetRankNum(0));

	std::string player_number = PLAYER_TAG + to_string(SceneManager::Instance().GetPlayerTexture(first_name));
	auto path = ConvertFilePath("Player/", player_number, ".png");
	_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());

	for (int i = 1; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name = PLAYER_TAG + to_string(GetRankNum(i));
		_player_rectwh.push_back(128 * (SceneManager::Instance().GetPlayerTexture(name) - 1));
	}

	//! material
	Material material;
	material.Diffuse  = Color(1.0f, 1.0f, 1.0f); // �A�e�̃O���f�[�V���� ���邢����
	material.Ambient  = Color(1.0f, 1.0f, 1.0f); // �x�[�X�̐F�@�Â�����
	material.Specular = Color(1.0f, 1.0f, 1.0f); // �e�J��
	material.Power    = 10.0f;                   // �e�J���̌��ʂ̋���

	_player_model->SetMaterial(material);

	//! camera
	Viewport view       = GraphicsDevice.GetViewport();
	Vector3  camera_pos = Vector3(0, 0, -10);
	Vector3  look_pos   = Vector3_Zero;

	SceneCamera::Instance().SetLookAt(camera_pos, look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(60.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	//!�v���C���[�̏����ݒ�
	_player_model->SetScale(5.0f);
	_player_model->SetPosition(Vector3(-5, -3, 0));
	_player_model->SetRotation(0, 180, 0);
	_player_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");
	_player_model->SetTrackEnable(5, TRUE);

	//�w�i�̍��W
	_background_position = Vector3(0, 0, 10000);

	return true;
}

/*
* @fn ���U���g�̍X�V
*/
int ResultScene::Update()
{
	AudioManager::Instance().ResultBgmPlay();
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		auto pad = InputManager::Instance().GetGamePad(PLAYER_TAG + std::to_string(i + 1));
		pad->Refresh();
		if (pad->ButtonDown(BUTTON_INFO::BUTTON_A))
		{
			AudioManager::Instance().ResultBgmStop();
			_player_model->SetTrackPosition(5, 0);
			_player_model->SetTrackEnable(5, false);
			SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::TITLE);
		}
	}
	return 0;
}

/*
* @fn ���U���g��2D�`��
*/
void ResultScene::Draw2D()
{
	SpriteBatch.Draw(*_background,_background_position);

	SpriteBatch.Draw(*_light, Vector3(0, 0, 10000));

	SpriteBatch.Draw(*_score_sprite, Vector3(150,600,0), RectWH((int)(GetRankNum(0) / 1000) * 64, 0, 64, 64),
		(DWORD)Color_White, Vector3_Zero, Vector3(32, 32, 0), 1.5f);

	for (int i = 1; i < 4; i++)
	{
		SpriteBatch.Draw(*_score_sprite, Vector3(96 * i + 150, 600, 0), RectWH((int)((GetRankNum(0) % 1000) / 100) * 64, 0, 64, 64),
			(DWORD)Color_White,Vector3_Zero, Vector3(32,32,0),1.5f);
	}

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		SpriteBatch.Draw(*_robot_fece, Vector3(850, 120 + 205 * i, 10000), RectWH(_player_rectwh[i], 0, 128, 128));
		SpriteBatch.Draw(*_score_sprite, Vector3(980, 175 + (210 * i), 0), RectWH((int)(GetRankNum(i) / 1000) * 64, 0, 64, 64),
			(DWORD)Color_White, Vector3_Zero, Vector3(32, 32, 0), 0.5f);
		for (int j = 1; j < PLAYER_COUNT_MAX; j++)
		{
			SpriteBatch.Draw(*_score_sprite, Vector3(980 + 32 * j, 175 + (210 * i), 0), RectWH((int)((GetRankNum(i) % 1000) / 100) * 64, 0, 64, 64),
				(DWORD)Color_White, Vector3_Zero, Vector3(32, 32, 0), 0.5f);
		}
	}
}
/*
* @fn ���U���g��3D�`��
*/
void ResultScene::Draw3D()
{
	Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
	SceneCamera::Instance().SetSceneCamera();

	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetParameter("vp", vp);
	_shader->SetTechnique("UnlitAnimationModel");
	_player_model->SetTrackPosition(5, _animation_count);
	_animation_count += GameTimer.GetElapsedSecond();
	_player_model->Draw(_shader);
}
/*
* @fn �����̐��𐔂���
*/
void ResultScene::ArrivalCount()
{
	_arrival_count = 1;

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//i�Ԗڂ̃|�C���g�Ƃ��̎��̏��ʂ̃|�C���g��������������1�ʂɂȂ�l�̃J�E���g�𑝂₷�B
		if (GetPoints(i) == GetPoints(i + 1)) {
			_arrival_count++;
		}
		else
		{
			break;
		}
	}
}
/**
 * @fn ���U���g�f�[�^���珸���Ƀv���C���[�̏��ʂ��擾����
 * @param (player_num) ���ʂ����Ԗڂ̃v���C���[��
 * @return ���U���g�f�[�^���珸���Ƀv���C���[�̏��ʂ�Ԃ�
 */
int ResultScene::GetRankNum(int player_num)
{
	auto resultdata = SceneManager::Instance().GetResultData();
	return resultdata->ranknum[player_num];
}
/**
 * @fn ���U���g�f�[�^���珸���Ƀv���C���[�̃|�C���g���擾����
 * @param (player_num) ���ʂ����Ԗڂ̃v���C���[��
 * @return ���U���g�f�[�^���珸���Ƀv���C���[�̃|�C���g��Ԃ�
 */
int ResultScene::GetPoints	(int player_num)
{
	auto resultdata = SceneManager::Instance().GetResultData();
	return resultdata->points[player_num];
}
