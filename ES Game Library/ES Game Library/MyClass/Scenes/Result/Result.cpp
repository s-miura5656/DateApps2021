#include"Result.h"
/*
* @fn リザルトの初期化
* @param　なし
* @return　なし
*/
void Result::Initialize()
{
	result = GraphicsDevice.CreateSpriteFromFile(_T("ResultSprite/Result.png"));
}
/*
* @fn リザルトの更新
* @param　なし
* @return　なし
*/
void Result::Update()
{

}
/*
* @fn リザルトの描画
* @param　なし
* @return　なし
*/
void Result::Draw()
{
	SpriteBatch.Draw(*result, Vector3(0, 0, 0));
}