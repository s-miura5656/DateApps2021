#include"ResultScene.h"
#include"../../Data/WordsTable.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include "../../Data/MyAlgorithm.h"
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
	_i_player_data = new IPrayerData;
	auto data = SceneManager::Instance().GetResultData();

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
	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f); // 陰影のグラデーション 明るい部分
	material.Ambient = Color(1.0f, 1.0f, 1.0f); // ベースの色　暗い部分
	material.Specular = Color(1.0f, 1.0f, 1.0f); // テカリ
	material.Power = 10.0f; // テカリの効果の強さ

	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/CharaShader.hlsl"));
	model = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	model->SetMaterial(material);
	model->SetRotation(0, 0, 0);
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

		if (pad->GetButtonBuffer(GamePad_Button2))
		{
			SceneManager::Instance().ChangeScene(SceneManager::TITLE);
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
	SpriteBatch.Draw(*ground, Vector3(0,0,10000));
	SpriteBatch.Draw(*totitle, Vector3(900, 600, 0));
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
	}
}
void ResultScene::Draw3D()
{
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
	//test
}