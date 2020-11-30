#include"ResultScene.h"
#include"../../Data/WordsTable.h"

/*
* @fn タイトルの初期化
* @param　なし
* @return　なし
*/
bool ResultScene::Initialize()
{
	result = GraphicsDevice.CreateSpriteFromFile(_T("ResultSprite/Result.png"));
	return true;
}
/*
* @fn タイトルの更新
* @param　なし
* @return　なし
*/
int ResultScene::Update()
{
	auto pad = ControllerManager::Instance().GetController(PLAYER_TAG + std::to_string(1));

	if (pad->GetButtonBuffer(GamePad_Button1))
	{
		//exit(0)
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
	SpriteBatch.Draw(*result, Vector3(0, 0, 0));
}
void ResultScene::Draw3D()
{
}