#include"ResultScene.h"
#include"../../Data/WordsTable.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include "../../Managers/InputManager/InputManager.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Data/IData.h"

ResultScene::ResultScene()
{

}

ResultScene::~ResultScene()
{

}

/*
* @fn リザルトの初期化
*/
bool ResultScene::Initialize()
{
	ArrivalCount();

	//! file
	_player_rank_num = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/number.png"));
	_background		 = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/ground.png"));
	_totitle	     = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/button.png"));
	_font			 = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 100);
	_shader			 = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	_player_model	 = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));

	_player_model->SetRotation(0, 180, 0);
	_player_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//プレイヤーごとにテクスチャを用意する。
		auto path = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(GetRankNum(i)), ".png");
		SPRITE texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
		_texture.push_back(texture);
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
	Vector3 _camera_pos = Vector3(0, 0, -10);
	Vector3 _look_pos   = Vector3_Zero;

	SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(60.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	//!プレイヤーモデルのスケールの設定
	_player_model_big_scale   = 1.0;
	_player_model_small_scale = 0.5;

	//!プレイヤーのY座標の位置ずれ修正
	_player_big_position_x   = 0.8;
	_player_small_position_x = 1.2;

	//!プレイヤーの順位の座標の設定
	_player_rank_number_position_x = -15;
	_player_rank_number_position_y = -50;

	//!ポイントの順位のX座標の位置ずれ修正
	_point_small_text_position_x = 300;
	_point_big_text_position_x   = 330;

	//!ポイントのテキストのスケールの設定
	_text_small_size = Vector2(1.0, 1.0);
	_text_big_size   = Vector2(0.5, 0.5);

	//!ポイントの順位の座標の設定
	_point_big_text_position       = Vector2(110, 550);
	_point_small_text_position     = Vector2(150, 500);

	//!プレイヤーの座標の設定
	_player_big_position   = Vector3(-1.5, 0, -7.5);
	_player_small_position = Vector3(-1.8, 0, -7.5);

	//背景の座標
	_background_position = Vector3(0, 0, 10000);
	//シーン遷移の方法の座標
	_totitle_position    = Vector3(900, 600, 0);

	return true;
}

/*
* @fn リザルトの更新
*/
int ResultScene::Update()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		auto pad = InputManager::Instance().GetGamePad(PLAYER_TAG + std::to_string(i + 1));
		pad->Refresh();
		//パンチを出すボタンがおされたときにタイトルへシーン遷移する。
		if (pad->ButtonDown(BUTTON_INFO::BUTTON_B))
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

	SpriteBatch.Draw(*_totitle,_totitle_position);
	
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		SpriteBatch.DrawString(_font, PointTextPosition(i), Color(255, 0, 0), _T("%d"), GetPoints(i));
		SpriteBatch.Draw(*_player_rank_num, PlayerRankNumberPositionCalculation(i) + Vector3(0,-50,0), 
			RectWH((GetRankNum(i) - 1) * 128, 0, 128, 64), 1,Vector3_Zero,Vector3_Zero, TextSizeCalculation(i));
	}
}
/*
* @fn リザルトの3D描画
*/
void ResultScene::Draw3D()
{
	Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
	SceneCamera::Instance().SetSceneCamera();

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		_shader->SetTexture("m_Texture", *_texture[i]);
		_shader->SetParameter("vp", vp);
		_player_model->SetScale(PlayerScaleCalculation(i));
		_player_model->SetPosition(PlayerPositionCalculation(i));
		_player_model->Draw(_shader);
	}
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
int ResultScene::GetPoints(int player_num)
{
	auto resultdata = SceneManager::Instance().GetResultData();
	return resultdata->points[player_num];
}

/**
 * @brief　プレイヤーモデルのスケールを設定する
 * @param (player_num) 順位が何番目のプレイヤーか
 * @return プレイヤーのスケールにセットするfloat型の値で返す
 */
float ResultScene::PlayerScaleCalculation(int player_num)
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
Vector2 ResultScene::TextSizeCalculation(int player_num) 
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
Vector3 ResultScene::PlayerPositionCalculation(int player_num)
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
	}

	return pl_pos;
}

/**
 * @brief　プレイヤーの座標を設定する
 * @param (player_num) 順位が何番目のプレイヤーか
 * @return プレイヤーの座標をVector3型の値で返す
 */
Vector3 ResultScene::PlayerRankNumberPositionCalculation(int player_num)
{
	Vector3 pl_rank_pos = (Vector3_Zero);

	if (player_num < _arrival_count) {
		pl_rank_pos.x = PointTextPosition(player_num).x + _player_rank_number_position_x;
		pl_rank_pos.y = PointTextPosition(player_num).y + _player_rank_number_position_y;
	}
	else 
	{
		pl_rank_pos.x = PointTextPosition(player_num).x + _player_rank_number_position_x;
		pl_rank_pos.y = PointTextPosition(player_num).y + _player_rank_number_position_y;
	}

	return pl_rank_pos;
}

/**
 * @brief　ポイントの座標を設定する
 * @param (player_num) 順位が何番目のプレイヤーか
 * @return ポイントの座標をVector2型の値で返す
 */
Vector2 ResultScene::PointTextPosition(int player_num)
{
	Vector2 pointpos;

	if (player_num < _arrival_count) {
		pointpos    = _point_big_text_position;
		pointpos.x += _point_big_text_position_x * player_num;
	}
	else {
		pointpos    = _point_small_text_position;
		pointpos.x += _point_small_text_position_x * (player_num - _arrival_count + 1);
	}

	return pointpos;
}