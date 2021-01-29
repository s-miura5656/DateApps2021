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
* @fn リザルトの初期化
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
    _first_score_sprite  = ResouceManager::Instance().LordSpriteFile(_T("NumberSprite/namber_vertical.png"));

	//!ロボUI初期設定
	std::string first_name = PLAYER_TAG + to_string(GetRankNum(0));

	std::string player_number = PLAYER_TAG + to_string(SceneManager::Instance().GetPlayerTexture(first_name));
	auto path = ConvertFilePath("Player/", player_number, ".png");
	_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());

	for (int i = 1; i < PLAYER_COUNT_MAX; i++)
	{
		_small_score_scale[i - 1] = 5.0f;
		_acceleration[i - 1] = 0;
		std::string name = PLAYER_TAG + to_string(GetRankNum(i));
		_player_rectwh.push_back(128 * (SceneManager::Instance().GetPlayerTexture(name) - 1));
	}
	//! material
	Material material;
	material.Diffuse  = Color(1.0f, 1.0f, 1.0f); // 陰影のグラデーション 明るい部分
	material.Ambient  = Color(1.0f, 1.0f, 1.0f); // ベースの色　暗い部分
	material.Specular = Color(1.0f, 1.0f, 1.0f); // テカリ
	material.Power    = 10.0f;                   // テカリの効果の強さ

	_player_model->SetMaterial(material);

	//! camera
	Viewport view       = GraphicsDevice.GetViewport();
	Vector3  camera_pos = Vector3(0, 0, -10);
	Vector3  look_pos   = Vector3_Zero;

	SceneCamera::Instance().SetLookAt(camera_pos, look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(60.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	for (int i = 0; i < 5; i++)
	{
		_player_model->SetTrackPosition(i, 0);
		_player_model->SetTrackEnable(i, false);
	}

	//!プレイヤーの初期設定
	_player_model->SetScale(5.0f);
	_player_model->SetPosition(Vector3(-5, -3, 0));
	_player_model->SetRotation(0, 180, 0);
	_player_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");
	_player_model->SetTrackEnable(5, TRUE);

	//背景の座標
	_background_position = Vector3(0, 0, 10000);
	_big_score_scale = 300.0f;
	return true;
}

/*
* @fn リザルトの更新
*/
int ResultScene::Update()
{
	for (int i = 2; i > -1; i--)
	{
		if (i == 2)
		{
			_small_score_scale[i] -= 0.5;
			_acceleration[i] += GameTimer.GetElapsedSecond();
		}
		else if (_acceleration[i + 1] >= 0.5)
		{
			_small_score_scale[i] -= 0.5;
			_acceleration[i] += GameTimer.GetElapsedSecond();
		}
	}

	if (_small_score_scale[0] <= 0.5)
	{
		_random_time += GameTimer.GetElapsedSecond();
		_random_number += 10;
	}

	if (_random_number >= 576)
	{
		_random_number = 0;
	}
	AudioManager::Instance().ResultBgmPlay();
	if (_random_time >= 3.5) 
	{
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
	}
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		if(_small_score_scale[i] <= 0.5)
			_small_score_scale[i] = 0.5f;
	}
	return 0;
}

/*
* @fn リザルトの2D描画
*/
void ResultScene::Draw2D()
{
	SpriteBatch.Draw(*_background,_background_position);

	SpriteBatch.Draw(*_light, Vector3(0, 0, 10000));
	if (_random_time >= 1.5)
	{
		SpriteBatch.Draw(*_first_score_sprite, Vector3(150, 600, 0), RectWH(0, (int)(GetPoints(0) / 1000) * 64, 64, 64),
			(DWORD)Color_White, Vector3_Zero, Vector3(32, 32, 0), 1.5f);
		SpriteBatch.Draw(*_first_score_sprite, Vector3(246, 600, 0), RectWH(0, (int)((GetPoints(0) % 1000) / 100) * 64, 64, 64),
			(DWORD)Color_White, Vector3(0, 0, 0), Vector3(32, 32, 0), 1.5f);
		SpriteBatch.Draw(*_first_score_sprite, Vector3(342, 600, 0), RectWH(0, (int)((GetPoints(0) % 1000) % 100 / 10) * 64, 64, 64),
			(DWORD)Color_White, Vector3(0, 0, 0), Vector3(32, 32, 0), 1.5f);
		SpriteBatch.Draw(*_first_score_sprite, Vector3(438, 600, 0), RectWH(0, (int)((GetPoints(0) % 1000) % 100 % 10) * 64, 64, 64),
			(DWORD)Color_White, Vector3(0, 0, 0), Vector3(32, 32, 0), 1.5f);
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			SpriteBatch.Draw(*_first_score_sprite, Vector3(150 + 96 * i, 600, 0), RectWH(0, _random_number , 64, 64),
				(DWORD)Color_White, Vector3_Zero, Vector3(32, 32, 0), 1.5f);
		}
	}
	for (int i = 0; i < PLAYER_COUNT_MAX - 1 ; i++)
	{
		if (_small_score_scale[i] < 5.0f)
		{
			SpriteBatch.Draw(*_robot_fece, Vector3(850, 120 + 205 * i, 10000), RectWH(_player_rectwh[i], 0, 128, 128));
			SpriteBatch.Draw(*_score_sprite, Vector3(1012, 175 + (210 * i), 0), RectWH((int)(GetPoints(i + 1) / 1000) * 64, 0, 64, 64), 
				(DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), _small_score_scale[i]);
			SpriteBatch.Draw(*_score_sprite, Vector3(1044, 175 + (210 * i), 0), RectWH((int)((GetPoints(i + 1) % 1000) / 100) * 64, 0, 64, 64),
				(DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), _small_score_scale[i]);
			SpriteBatch.Draw(*_score_sprite, Vector3(1076, 175 + (210 * i), 0), RectWH((int)((GetPoints(i + 1) % 1000) % 100 / 10) * 64, 0, 64, 64),
				(DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), _small_score_scale[i]);
			SpriteBatch.Draw(*_score_sprite, Vector3(1108, 175 + (210 * i), 0), RectWH((int)((GetPoints(i + 1) % 1000) % 100 % 10) * 64, 0, 64, 64), 
				(DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), _small_score_scale[i]);
		}
	}
}
/*
* @fn リザルトの3D描画
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
* @fn 同着の数を数える
*/
void ResultScene::ArrivalCount()
{
	_arrival_count = 1;

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//i番目のポイントとその次の順位のポイントが同じだったら1位になる人のカウントを増やす。
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
 * @fn リザルトデータから昇順にプレイヤーの順位を取得する
 * @param (player_num) 順位が何番目のプレイヤーか
 * @return リザルトデータから昇順にプレイヤーの順位を返す
 */
int ResultScene::GetRankNum(int player_num)
{
	auto resultdata = SceneManager::Instance().GetResultData();
	return resultdata->ranknum[player_num];
}
/**
 * @fn リザルトデータから昇順にプレイヤーのポイントを取得する
 * @param (player_num) 順位が何番目のプレイヤーか
 * @return リザルトデータから昇順にプレイヤーのポイントを返す
 */
int ResultScene::GetPoints	(int player_num)
{
	auto resultdata = SceneManager::Instance().GetResultData();
	return resultdata->points[player_num];
}
