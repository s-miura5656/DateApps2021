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
	AudioManager::Instance().ResultBgmStop();
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
	_font                = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 50);
	_shader  	         = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	_player_model        = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));

	_player_model->SetRotation(0, 180, 0);
	_player_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//プレイヤーごとにテクスチャを用意する。
		auto path = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(GetRankNum(0)), ".png");
		_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
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

	//!プレイヤーモデルのスケールの設定
	_player_model_big_scale   = 1.0;
	_player_model_small_scale = 0.5;

	//!プレイヤーのX座標の位置ずれ修正
	_player_big_position_x   = 0.8;
	_player_small_position_x = 1.5;

	//!ポイントの順位のX座標の位置ずれ修正
	_point_small_text_position_correction = Vector2 (420,25);
	_point_big_text_position_correction = Vector2(420, 25);

	//!ポイントのテキストのスケールの設定
	_text_big_size   = Vector2(1.0, 1.0);
	_text_small_size = Vector2(0.5, 0.5);

	//!プレイヤーの順位の座標の設定
	_player_big_rank_number_position = Vector2(0,-50);
	_player_small_rank_number_position = Vector2(0, -30);

	//!ポイントの順位の座標の設定
	_point_big_text_position       = Vector2(430, 430);
	_point_small_text_position     = Vector2(220, 400);

	//!プレイヤーの座標の設定
	_player_big_position   = Vector3(-0.6, 0, -7.5);
	_player_small_position = Vector3(-3.0, 0.2, -7.5);

	//背景の座標
	_background_position = Vector3(0, 0, 10000);
	//シーン遷移の方法の座標
	_totitle_position    = Vector3(900, 640, 0);

	return true;
}

/*
* @fn リザルトの更新
*/
int ResultScene::Update()
{
	AudioManager::Instance().ResultBgmPlay();
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		auto pad = InputManager::Instance().GetGamePad(PLAYER_TAG + std::to_string(i + 1));
		pad->Refresh();
		//パンチを出すボタンがおされたときにタイトルへシーン遷移する。
		if (pad->ButtonDown(BUTTON_INFO::BUTTON_A))
		{
			SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::TITLE);
		}
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
	SpriteBatch.Draw(*_robot_win, Vector3(45, 105, 10000), RectWH((GetRankNum(0) - 1) * 512, 0, 512, 512));
	SpriteBatch.DrawString(_font, Vector2(200, 600), Color(255, 255, 255), _T("%dpt"), GetPoints(0));

	for (int i = 0; i < PLAYER_COUNT_MAX - 1; i++)
	{
		SpriteBatch.Draw(*_robot_fece, Vector3(850, 120 + 205 * i, 10000),RectWH(128 * i,0, 128,128));
		SpriteBatch.DrawString(_font, Vector2(980, 170 + 210 * (i)), Color(255, 0, 0), _T("%dpt"), GetPoints(i + 1));
	}
}
/*
* @fn リザルトの3D描画
*/
void ResultScene::Draw3D()
{
	Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
	SceneCamera::Instance().SetSceneCamera();

	//_shader->SetTexture("m_Texture", *_texture);
	//_shader->SetParameter("vp", vp);
	//_shader->SetTechnique("UnlitAnimationModel");
	//_player_model->SetScale(5.0f);
	//_player_model->SetPosition(Vector3(-6,-3,0));
	//_player_model->Draw(_shader);
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

/**
 * @brief　プレイヤーモデルのスケールを設定する
 * @param (player_num) 順位が何番目のプレイヤーか
 * @return プレイヤーのスケールにセットするfloat型の値で返す
 */
float ResultScene::SetPlayerScale(int player_num)
{
	float pl_model_scale;

	if (player_num < _arrival_count) {
		pl_model_scale = _player_model_big_scale;
	}
	else
	{
		pl_model_scale = _player_model_small_scale;
	}

	return pl_model_scale;
}

/**
 * @brief　テキストのサイズを設定する
 * @param (player_num) 順位が何番目のプレイヤーか
 * @return テキストのサイズをVector2型の値で返す
 */
Vector2 ResultScene::SetTextSize(int player_num)
{
	Vector2 text_size;
	
	if (player_num < _arrival_count) {
		text_size = Vector2(_text_big_size);
	}
	else
	{
		text_size = Vector2(_text_small_size);
	}

	return text_size;
}

/**
 * @brief　プレイヤーの座標を設定する
 * @param (player_num) 順位が何番目のプレイヤーか
 * @return プレイヤーの座標をVector3型の値で返す
 */
Vector3 ResultScene::SetPlayerPosition(int player_num)
{
	Vector3 pl_pos;

	if (player_num < _arrival_count) {
		pl_pos    = _player_big_position;
		pl_pos.x += _player_big_position_x * player_num;
	}
	else
	{
		pl_pos    = _player_small_position;
		pl_pos.x += _player_small_position_x * player_num;
		pl_pos.y += -0.2 * player_num;
	}

	return pl_pos;
}

/**
 * @brief　プレイヤーの座標を設定する
 * @param (player_num) 順位が何番目のプレイヤーか
 * @return プレイヤーの順位の座標をVector3型の値で返す
 */
Vector3 ResultScene::SetPlayerRankNumberPosition(int player_num)
{
	Vector3 pl_rank_pos = (Vector3_Zero);

	if (player_num < _arrival_count) 
	{
		pl_rank_pos.x = SetPointTextPosition(player_num).x;
		pl_rank_pos.y = SetPointTextPosition(player_num).y + _player_big_rank_number_position.y;
	}
	else
	{
		pl_rank_pos.x = SetPointTextPosition(player_num).x;
		pl_rank_pos.y = SetPointTextPosition(player_num).y + _player_small_rank_number_position.y;
	}

	return pl_rank_pos;
}

/**
 * @brief　ポイントの座標を設定する
 * @param (player_num) 順位が何番目のプレイヤーか
 * @return ポイントの座標をVector2型の値で返す
 */
Vector2 ResultScene::SetPointTextPosition(int player_num)
{
	Vector2 pointpos;

	if (player_num < _arrival_count) {
		pointpos    = _point_big_text_position;
	}
	else {
		pointpos    = _point_small_text_position;
		pointpos += Vector2(_point_small_text_position_correction.x * (player_num - _arrival_count), 
			                _point_small_text_position_correction.y * (player_num - _arrival_count + 1));
	}

	return pointpos;
}