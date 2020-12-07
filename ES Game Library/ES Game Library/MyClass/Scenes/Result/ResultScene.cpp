#include"ResultScene.h"
#include"../../Data/WordsTable.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
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
	model = ResouceManager::Instance().LoadModelFile(_T("ResultSprite/robot.x"));

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
}
void ResultScene::Draw3D()
{
	GraphicsDevice.SetCamera(camera);
	model->Draw();
}