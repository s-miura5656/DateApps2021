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

	ground = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/ground.png"));
	champion = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/Champion.png"));
	totitle = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/Totitle.png"));
	model = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation ver3.X"));
	txt = ResouceManager::Instance().LordFontFile(_T("Yu Gothic UI"), 70);

	camera->SetView(Vector3(0, 0, -3), Vector3(0, 0, 0)); // 視点
	camera->SetPerspectiveFieldOfView(45.0f, 16.0f / 9.0f, 1.0f, 10000.0f); // 視界

	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f); // 陰影のグラデーション 明るい部分
	material.Ambient = Color(1.0f, 1.0f, 1.0f); // ベースの色　暗い部分
	material.Specular = Color(1.0f, 1.0f, 1.0f); // テカリ
	material.Power = 10.0f; // テカリの効果の強さ

	model->SetMaterial(material);
	model->SetPosition(Vector3(-1, -0.5, 0));
	model->SetRotation(0, 0, 0);
	model->SetScale(1.5f);

	_i_player_data = new IPrayerData;

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);
		if (_i_player_data->GetRankNum(tag) == 0)
		{
			num = _i_player_data->GetRankNum(tag) + 1;
			break;
		}
	}
	std::string playertag = PLAYER_TAG + std::to_string(num);
	if (num == 1) {
		auto path = ConvertFilePath("Player/", playertag, ".png");
		_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
	}
	else if (num == 2) {
		auto path = ConvertFilePath("Player/", playertag, ".png");
		_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
	}
	else if (num == 3) {
		auto path = ConvertFilePath("Player/", playertag, ".png");
		_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
	}
	else if (num == 4) {
		auto path = ConvertFilePath("Player/", playertag, ".png");
		_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
	}
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/CharaShader.hlsl"));
	model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");
	return true;
}
/*
* @fn タイトルの更新
* @param　なし
* @return　なし
*/
int ResultScene::Update()
{
	return 0;
}

/*
* @fn タイトルの描画
* @param　なし
* @return　なし
*/
void ResultScene::Draw2D()
{

	SpriteBatch.Draw(*ground, Vector3(0,0,10000));
	SpriteBatch.Draw(*champion, Vector3(800,50,0));
	SpriteBatch.Draw(*totitle, Vector3(800, 600, 0));
	SpriteBatch.DrawString(txt, Vector2(750, 100), Color(255, 255, 0), _T("チャンピオンはプレイヤー%d"), num);
}
void ResultScene::Draw3D()
{
	Matrix vp = camera->GetViewProjectionMatrix();
	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetTechnique("FixModel");
	_shader->SetParameter("vp", vp);
	GraphicsDevice.SetCamera(camera);
	model->Draw(_shader);
}