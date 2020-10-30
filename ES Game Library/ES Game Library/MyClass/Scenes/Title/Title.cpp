#include"Title.h"
/*
* @fn タイトルの初期化
* @param　なし
* @return　なし
*/
void Title::Initialize()
{
	title = GraphicsDevice.CreateSpriteFromFile(_T("TitleSprite/Title.png"));
}
/*
* @fn タイトルの更新
* @param　なし
* @return　なし
*/
void Title::Update()
{

}
/*
* @fn タイトルの描画
* @param　なし
* @return　なし
*/
void Title::Draw()
{
	SpriteBatch.Draw(*title,Vector3(0,0,0));
}