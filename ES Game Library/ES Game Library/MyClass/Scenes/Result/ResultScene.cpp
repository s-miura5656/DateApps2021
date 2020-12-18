#include"ResultScene.h"
#include"../../Data/WordsTable.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Data/IData.h"

ResultScene::ResultScene()
{
	i_player_data = new IPrayerData;
}
ResultScene::~ResultScene()
{
	delete i_player_data;
}
/*
* @fn タイトルの初期化
* @param　なし
* @return　なし
*/
bool ResultScene::Initialize()
{
	ArrivalCount();
	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f); // 陰影のグラデーション 明るい部分
	material.Ambient = Color(1.0f, 1.0f, 1.0f); // ベースの色　暗い部分
	material.Specular = Color(1.0f, 1.0f, 1.0f); // テカリ
	material.Power = 10.0f; // テカリの効果の強さ

	player_rank_num = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/number.png"));
	background = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/ground.png"));
	totitle = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/button.png"));
	font = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 100);
	shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	player_model = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	player_model->SetMaterial(material);
	player_model->SetRotation(0, 0, 0);
	player_model->RegisterBoneMatricesByName(shader, "WorldMatrixArray", "NumBones");

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//プレイヤーごとにテクスチャを用意する。
		auto path = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(GetRankNum(i)), ".png");
		SPRITE _texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
		texture.push_back(_texture);
	}

	Viewport view = GraphicsDevice.GetViewport();
	Vector3 _camera_pos = Vector3(0, 0, -10);
	Vector3 _look_pos = Vector3(0, 0, 0);

	SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(60.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	ControllerManager::Instance().CreateGamePad(PLAYER_TAG + std::to_string(1));
	ControllerManager::Instance().SetGamePadMaxCount(PLAYER_COUNT_MAX);
	return true;
}
/*
* @fn タイトルの更新
* @param　なし
* @return　なし
*/
int ResultScene::Update()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		auto pad = ControllerManager::Instance().GetController(PLAYER_TAG + std::to_string(i + 1));
		pad->GamePadRefresh();
		//パンチを出すボタンがおされたときにタイトルへシーン遷移する。
		if (pad->GetButtonBuffer(GamePad_Button2))
		{
			SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::TITLE);
		}
	}
	return 0;
}

/*
* @fn タイトルの描画
* @param　なし
* @return　なし
*/
void ResultScene::Draw2D()
{
	SpriteBatch.Draw(*background, Vector3(0, 0, 10000));
	SpriteBatch.Draw(*totitle, Vector3(900, 600, 0));
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		SpriteBatch.DrawString(font, Vector2(PointTextPosition(i)), Color(255, 0, 0), _T("%d"), GetPoints(i));
		SpriteBatch.Draw(*player_rank_num, Vector3(PlayerRankNumberPositionCalculation(i)) + Vector3(0,-50,0), RectWH((GetRankNum(i) - 1) * 128, 0, 128, 64), 1, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector2(TextSizeCalculation(i)));
	}
}
void ResultScene::Draw3D()
{
	Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
	SceneCamera::Instance().SetSceneCamera();
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		shader->SetTexture("m_Texture", *texture[i]);
		shader->SetParameter("vp", vp);
		player_model->SetScale(PlayerScaleCalculation(i));
		player_model->SetPosition(PlayerPositionCalculation(i));
		player_model->Draw(shader);
	}
}
void ResultScene::ArrivalCount()
{
	arrival_count = 1;
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//i番目のポイントとその次の順位のポイントが同じだったら1位になる人のカウントを増やす。
		if (GetPoints(i) == GetPoints(i) + 1) {
			arrival_count++;
		}
		else
		{
			break;
		}
	}
}
int ResultScene::GetRankNum(int player_num)
{
	auto resultdata = SceneManager::Instance().GetResultData();
	return resultdata->ranknum[player_num];
}
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
	if (player_num < arrival_count) {
		pl_model_scale = 1.0;
	}
	else
	{
		pl_model_scale = 0.5;
	}
	return pl_model_scale;
}
/**
 * @brief　テキストのサイズを設定する
 * @param (player_num) 順位が何番目のプレイヤーか
 * @return テキストのサイズをVector2型の値で返す
 */
Vector2 ResultScene::TextSizeCalculation(int player_num) {
	Vector2 text_size;
	if (player_num < arrival_count) {
		text_size = Vector2(1.0,1.0);
	}
	else
	{
		text_size = Vector2(0.5, 0.5);
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
	if (player_num < arrival_count) {
		pl_pos = Vector3(-1.5 + (0.8 * player_num), 0, -7.5);
	}
	else
	{
		pl_pos = Vector3(-1.8 + (1.2 * player_num), 0, -7.5);
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
	if (player_num < arrival_count) {
		pl_rank_pos.x = PointTextPosition(player_num).x - 15;
		pl_rank_pos.y = PointTextPosition(player_num).y + -50;
	}
	else 
	{
		pl_rank_pos.x = PointTextPosition(player_num).x - 15;
		pl_rank_pos.y = PointTextPosition(player_num).y + -50;
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
	if (player_num < arrival_count) {
		pointpos = Vector2(110 + 300 * player_num,550);
	}
	else {
		pointpos = Vector2(150 + (330 * (player_num - arrival_count + 1)), 500);
	}
	return pointpos;
}