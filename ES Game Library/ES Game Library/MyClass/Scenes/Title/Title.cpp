#include"Title.h"
/*
* @fn �^�C�g���̏�����
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
void Title::Initialize()
{
	title = GraphicsDevice.CreateSpriteFromFile(_T("TitleSprite/Title.png"));
}
/*
* @fn �^�C�g���̍X�V
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
void Title::Update()
{

}
/*
* @fn �^�C�g���̕`��
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
void Title::Draw()
{
	SpriteBatch.Draw(*title,Vector3(0,0,0));
}