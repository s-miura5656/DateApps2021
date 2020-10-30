
#include"ResultScene.h"

bool ResultScene::FileInitialize()
{
	result = GraphicsDevice.CreateSpriteFromFile(_T("ResultSprite/Result.png"));

	return true;
}
/*
* @fn タイトルの初期化
* @param　なし
* @return　なし
*/
bool ResultScene::Initialize()
{

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
	SpriteBatch.Draw(*result, Vector3(0, 0, 0));
}
void ResultScene::Draw3D()
{
}