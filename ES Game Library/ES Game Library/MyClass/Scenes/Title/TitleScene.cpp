#include"TitleScene.h"
#include"../../Data/WordsTable.h"
#include"../../Data/ModelAnimation.h"

/*
* @fn タイトルの初期化
* @param　なし
* @return　なし
*/
bool TitleScene::Initialize()
{
	_title = GraphicsDevice.CreateSpriteFromFile(_T("TitleSprite/Title.png"));

	ControllerManager::Instance().SetGamePadMaxCount(PLAYER_COUNT_MAX);

	ControllerManager::Instance().CreateGamePad(PLAYER_TAG + std::to_string(1));

	for (int i = 0; i < 4; i++)
	{
		model[i] = GraphicsDevice.CreateModelFromFile(_T("Player/robot.x"));
	}
	

	item = GraphicsDevice.CreateModelFromFile(_T("TitleSprite/item_04.X"));


	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f); // 陰影のグラデーション 明るい部分
	material.Ambient = Color(1.0f, 1.0f, 1.0f); // ベースの色　暗い部分
	material.Specular = Color(1.0f, 1.0f, 1.0f); // テカリ
	material.Power = 10.0f; // テカリの効果の強さ

	for (int i = 0; i < 4; i++)
	{
		model[i]->SetMaterial(material);
		model[i]->SetPosition(Vector3(-4 + 3* i, 0, 0));
		model[i]->SetRotation(90, 0, 0);
		model[i]->SetScale(1.0f, 1.0f, 1.0f);
	}

	item->SetMaterial(material);
	item->SetScale(5.0f, 5.0f, 5.0f);
	item->SetRotation(270, 0, 0);
	

	camera->SetView(Vector3(0, 0, 0), Vector3(5, 0, 0)); // 視点
	camera->SetPerspectiveFieldOfView(45.0f, 16.0f / 9.0f, 1.0f, 10000.0f); // 視界

	
	GraphicsDevice.SetCamera(camera);

	return true;
}
/*
* @fn タイトルの更新
* @param　なし
* @return　なし
*/
int TitleScene::Update()
{
	auto pad = ControllerManager::Instance().GetController(PLAYER_TAG + std::to_string(1));
	
	if (pad->GetButtonBuffer(GamePad_Button1))
	{
		//exit(0);
	}


	// モデルの回転
	ModelRotation(Vector3(0.0f, 0.0f, 5.0f), model[0]);
	ModelRotation(Vector3(0.0f, 3.0f, 0.0f), item);

	// モデルの拡大縮小
	_scale = ModelScaling(5.f, 1.f, _scale, 0.05f, model[1]);
	model[1]->SetScale(Vector3_One * _scale);

	// モデルの点滅
	_alpha = ModelFlashing(1.0f, 0.0f, _alpha, 0.1f, model[2]);
	_alpha = ModelFlashing(1.0f, 0.0f, _alpha, 0.1f, item);

	// モデルのZ軸往復
	_bound = ModelBound(_bound, 0.0f, 5.0f, 2.0f, model[3]);

	return 0;
}

/*
* @fn タイトルの描画
* @param　なし
* @return　なし
*/
void TitleScene::Draw2D()
{
	//SpriteBatch.Draw(*_title, Vector3(0, 0, +10000.0f));
}
void TitleScene::Draw3D()
{
	//item->Draw();

	model[0]-> Draw();
	model[1]->Draw();
	model[3]->Draw();

	GraphicsDevice.BeginAlphaBlend();
	model[2]->DrawAlpha(_alpha);
	item->DrawAlpha(_alpha);
	GraphicsDevice.EndAlphaBlend();

	GraphicsDevice.SetCamera(camera);
}

