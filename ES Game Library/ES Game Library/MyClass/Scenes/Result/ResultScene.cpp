
#include"ResultScene.h"

bool ResultScene::FileInitialize()
{
	result = GraphicsDevice.CreateSpriteFromFile(_T("ResultSprite/Result.png"));

	return true;
}
/*
* @fn �^�C�g���̏�����
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
bool ResultScene::Initialize()
{

	return true;
}
/*
* @fn �^�C�g���̍X�V
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
int ResultScene::Update()
{
	return 0;
}

/*
* @fn �^�C�g���̕`��
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
void ResultScene::Draw2D()
{
	SpriteBatch.Draw(*result, Vector3(0, 0, 0));
}
void ResultScene::Draw3D()
{
}