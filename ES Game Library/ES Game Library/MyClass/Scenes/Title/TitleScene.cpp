#include"TitleScene.h"

bool TitleScene::FileInitialize()
{
	_title = GraphicsDevice.CreateSpriteFromFile(_T("TitleSprite/Title.png"));

	return true;
}
/*
* @fn �^�C�g���̏�����
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
bool TitleScene::Initialize()
{

	return true;
}
/*
* @fn �^�C�g���̍X�V
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
int TitleScene::Update()
{
	return 0;
}

/*
* @fn �^�C�g���̕`��
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
void TitleScene::Draw2D()
{
	SpriteBatch.Draw(*_title, Vector3(0, 0, 0));
}
void TitleScene::Draw3D()
{
}

