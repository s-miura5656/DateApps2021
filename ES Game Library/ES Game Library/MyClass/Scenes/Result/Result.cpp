#include"Result.h"
/*
* @fn ���U���g�̏�����
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
void Result::Initialize()
{
	result = GraphicsDevice.CreateSpriteFromFile(_T("ResultSprite/Result.png"));
}
/*
* @fn ���U���g�̍X�V
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
void Result::Update()
{

}
/*
* @fn ���U���g�̕`��
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
void Result::Draw()
{
	SpriteBatch.Draw(*result, Vector3(0, 0, 0));
}