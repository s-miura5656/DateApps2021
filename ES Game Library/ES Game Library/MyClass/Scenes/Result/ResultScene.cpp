#include"ResultScene.h"
#include"../../Data/WordsTable.h"

/*
* @fn �^�C�g���̏�����
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
bool ResultScene::Initialize()
{
	result = GraphicsDevice.CreateSpriteFromFile(_T("ResultSprite/Result.png"));
	return true;
}
/*
* @fn �^�C�g���̍X�V
* @param�@�Ȃ�
* @return�@�Ȃ�
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