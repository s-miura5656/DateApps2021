#include"ResultScene.h"
#include"../../Data/WordsTable.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Data/IData.h"

ResultScene::ResultScene()
{

}
ResultScene::~ResultScene()
{

}
/*
* @fn タイトルの初期化
* @param　なし
* @return　なし
*/
bool ResultScene::Initialize()
{
<<<<<<< HEAD
	AllPosCalculation();
=======
<<<<<<< HEAD
	player = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/number.png"));
	ground = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/ground.png"));
	totitle = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/button.png"));
	model = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	txt = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 70);
	auto _effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/effekseer_break02/break_effect.efk"));
=======
	_i_player_data = new IPrayerData;
	auto data = SceneManager::Instance().GetResultData();
>>>>>>> cf893e710f413e5dde5084f45cb4a2ee7ff9259e

	arrival = 1;
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		if (data->points[i] == data->points[i + 1]) {
			arrival++;
		}
		else
		{
			break;
		}
	}
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		auto path = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(data->ranknum[i]), ".png");
		SPRITE texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
		_texture.push_back(texture);
		pos.push_back(Vector3(-1.5 + (1 * i), -0.3, 0));
	}
>>>>>>> fd01da56e21be856ceeb0274213800e37c991da6
	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f); // 陰影のグラデーション 明るい部分
	material.Ambient = Color(1.0f, 1.0f, 1.0f); // ベースの色　暗い部分
	material.Specular = Color(1.0f, 1.0f, 1.0f); // テカリ
	material.Power = 10.0f; // テカリの効果の強さ

<<<<<<< HEAD
	player_rank_num = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/number.png"));
	background = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/ground.png"));
	totitle = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/button.png"));
	font = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 100);
	shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	player_model = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	player_model->SetMaterial(material);
	player_model->SetRotation(0, 0, 0);
	player_model->RegisterBoneMatricesByName(shader, "WorldMatrixArray", "NumBones");
=======
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/CharaShader.hlsl"));
	model = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	model->SetMaterial(material);
	model->SetRotation(0, 0, 0);
<<<<<<< HEAD
	model->SetScale(1.5f);

	auto data = SceneManager::Instance().GetResultData();

	auto path = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(data->ranknum[0]), ".png");
	_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());

	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");
>>>>>>> fd01da56e21be856ceeb0274213800e37c991da6

	Viewport view = GraphicsDevice.GetViewport();
	Vector3 _camera_pos = Vector3(0, 0, -10);
	Vector3 _look_pos = Vector3(0, 0, 0);

	SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(60.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

<<<<<<< HEAD
	ControllerManager::Instance().CreateGamePad(PLAYER_TAG + std::to_string(1));
	ControllerManager::Instance().SetGamePadMaxCount(PLAYER_COUNT_MAX);
=======
=======
	model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");
	player = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/number.png"));
	ground = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/ground.png"));
	totitle = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/button.png"));
	txt = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 100);
	SceneCamera::Instance().SetView(Vector3(0, 0, -3), Vector3(0, 0, 0));
	SceneCamera::Instance().SetPerspectiveFieldOfView(45.0f, 16.0f, 9.0f, 1.0f, 10000.0f);

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);
		if (_i_player_data->GetRankNum(tag) == 0)
		{
			num = _i_player_data->GetRankNum(tag) + 1;
			break;
		}
	}

	ControllerManager::Instance().CreateGamePad(PLAYER_TAG + std::to_string(1));
	ControllerManager::Instance().SetGamePadMaxCount(PLAYER_COUNT_MAX);
	if (data->points[0] >= 1000) {
		fix = -30;
	}
	else if (data->points[0] >= 100) {
		fix = 0;
	}
	else if (data->points[0] >= 10) {
		fix = 30;
	}
>>>>>>> cf893e710f413e5dde5084f45cb4a2ee7ff9259e
>>>>>>> fd01da56e21be856ceeb0274213800e37c991da6
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
	auto data = SceneManager::Instance().GetResultData();
	SpriteBatch.Draw(*background, Vector3(0, 0, 10000));
	SpriteBatch.Draw(*totitle, Vector3(900, 600, 0));
<<<<<<< HEAD
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		SpriteBatch.DrawString(font, Vector2(point_text_position[i]), Color(255, 0, 0), _T("%d"), data->points[i]);
		SpriteBatch.Draw(*player_rank_num, Vector3(player_rank_num_position[i]) + Vector3(0,-50,0), RectWH((data->ranknum[i] - 1) * 128, 0, 128, 64), 1, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector2(TextSizeCalculation(i)));
=======
<<<<<<< HEAD

	//SpriteBatch.DrawString(txt, Vector2(960, 150), Color(255, 0, 0),_T("%d"), data->points[0]);
	//SpriteBatch.Draw(*player, Vector3(750, 130,0), RectWH((data->ranknum[0] - 1), 0, 128, 64),1,Vector3(0, 0, 0), Vector3(0, 0, 0), Vector2(1.5f, 1.5f));
	
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		SpriteBatch.DrawString(txt, Vector2(960, 150 + (105 * i)), Color(0, 0, 0), _T("%d"), data->points[i]);
		SpriteBatch.Draw(*player, Vector3(750 - 30 * i, 150 + (100 * i), 0), RectWH((data->ranknum[i] - 1) * 128, 0, 128, 64));
=======
	float pos_x;
	for (int i = 0; i < arrival; i++)
	{
		pos_x = 80 + 300 * i;
		SpriteBatch.DrawString(txt, Vector2(pos_x + fix,550), Color(255, 0, 0), _T("%d"), data->points[i]);
		SpriteBatch.Draw(*player, Vector3(pos_x, 450, 0), RectWH((data->ranknum[i] - 1) * 128, 0, 128, 64), 1, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector2(1.5f, 1.5f));
	}
	int count = 0;
	for (int i = arrival; i < PLAYER_COUNT_MAX; i++)
	{
		SpriteBatch.DrawString(txt, Vector2(pos_x + 400 + 300 * count, 500), Color(0, 0, 0), _T("%d"), data->points[i]);
		SpriteBatch.Draw(*player,Vector3(pos_x + 330 * i, 430,0),RectWH((data->ranknum[i] - 1) * 128,0,128,64));
		count++;
>>>>>>> cf893e710f413e5dde5084f45cb4a2ee7ff9259e
>>>>>>> fd01da56e21be856ceeb0274213800e37c991da6
	}
}
void ResultScene::Draw3D()
{
<<<<<<< HEAD
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
void ResultScene::AllPosCalculation()
{
	i_player_data = new IPrayerData;
	auto resultdata = SceneManager::Instance().GetResultData();

	arrival_count = 1;
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//i番目のポイントとその次の順位のポイントが同じだったら1位になる人のカウントを増やす。
		if (resultdata->points[i] == resultdata->points[i + 1]) {
			arrival_count++;
		}
		else
		{
			break;
		}
	}
	int point_text_fix[PLAYER_COUNT_MAX] = {};
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//プレイヤーごとにテクスチャを用意する。
		auto path = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(resultdata->ranknum[i]), ".png");
		SPRITE _texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
		texture.push_back(_texture);
		//ポイントの桁数によって位置を修正する。
		if (resultdata->points[0] >= 10 * (10 * i)) {
			point_text_fix[i] = 30 - 30 * i;
		}
	}
	int first_rank_ui_pos_x;
	for (int i = 0; i < arrival_count; i++)
	{
		first_rank_ui_pos_x = 80 + 300 * i + point_text_fix[i];
		point_text_position.push_back(Vector2(first_rank_ui_pos_x, 550));
		player_rank_num_position.push_back(Vector3(first_rank_ui_pos_x, 450, 0));
	}
	int count = 0;
	for (int i = arrival_count; i < PLAYER_COUNT_MAX; i++)
	{
		point_text_position.push_back(Vector2(first_rank_ui_pos_x + 330 + 330 * count, 500));
		player_rank_num_position.push_back(Vector3(first_rank_ui_pos_x + 330 * i, 460, 0));
		count++;
	}
}
float ResultScene::PlayerScaleCalculation(int num)
{
	float scale;
	if (num < arrival_count) {
		scale = 1.0;
	}
	else
	{
		scale = 0.5;
	}
	return scale;
}
Vector2 ResultScene::TextSizeCalculation(int num) {
	Vector2 size;
	if (num < arrival_count) {
		size = Vector2(1.0,1.0);
	}
	else
	{
		size = Vector2(0.5, 0.5);
	}
	return size;
}
Vector3 ResultScene::PlayerPositionCalculation(int num) 
{
	Vector3 pos;
	if (num < arrival_count) {
		pos = Vector3(-1.5 + (0.8 * num), 0, -7.5);
	}
	else
	{
		pos = Vector3(-1.8 + (1.2 * num), 0, -7.5);
	}
	return pos;
=======
<<<<<<< HEAD
	//model->SetTrackPosition(1, GameTimer.GetElapsedSecond() * 2.0f);
	//model->SetTrackEnable(0, TRUE);

	Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetTechnique("FixModel");
	_shader->SetParameter("vp", vp);
	model->SetPosition(Vector3(-1.0f, -0.8f, -7.5f));
	model->Draw(_shader);
=======
	Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
	GraphicsDevice.SetCamera(SceneCamera::Instance().GetCamera());
	for (int i = 0; i < arrival; i++)
	{
		_shader->SetTexture("m_Texture", *_texture[i]);
		_shader->SetTechnique("FixModel");
		_shader->SetParameter("vp", vp);
		model->SetScale(1.0f);
		model->SetPosition(pos[i]);
		model->Draw(_shader);
	}
	for (int i = arrival; i < PLAYER_COUNT_MAX; i++)
	{
		_shader->SetTexture("m_Texture", *_texture[i]);
		_shader->SetTechnique("FixModel");
		_shader->SetParameter("vp", vp);
		model->SetScale(0.5f);
		model->SetPosition(pos[i] + Vector3(0,0.1,0));
		model->Draw(_shader);
	}
>>>>>>> cf893e710f413e5dde5084f45cb4a2ee7ff9259e
	//test
	//テスト
>>>>>>> fd01da56e21be856ceeb0274213800e37c991da6
}