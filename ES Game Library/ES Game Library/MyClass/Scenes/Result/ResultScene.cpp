#include"ResultScene.h"
#include"../../Data/WordsTable.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
/*
* @fn �^�C�g���̏�����
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
bool ResultScene::Initialize()
{
	ground = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/ground.png"));
	champion = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/Champion.png"));
	totitle = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/Totitle.png"));
	model = ResouceManager::Instance().LoadModelFile(_T("ResultSprite/robot.x"));

	camera->SetView(Vector3(0, 0, -3), Vector3(0, 0, 0)); // ���_
	camera->SetPerspectiveFieldOfView(45.0f, 16.0f / 9.0f, 1.0f, 10000.0f); // ���E

	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f); // �A�e�̃O���f�[�V���� ���邢����
	material.Ambient = Color(1.0f, 1.0f, 1.0f); // �x�[�X�̐F�@�Â�����
	material.Specular = Color(1.0f, 1.0f, 1.0f); // �e�J��
	material.Power = 10.0f; // �e�J���̌��ʂ̋���

	model->SetMaterial(material);
	model->SetPosition(Vector3(-1, -0.5, 0));
	model->SetRotation(0, 0, 0);
	model->SetScale(1.5f);

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
	SpriteBatch.Draw(*ground, Vector3(0,0,10000));
	SpriteBatch.Draw(*champion, Vector3(800,50,0));
	SpriteBatch.Draw(*totitle, Vector3(800, 600, 0));
}
void ResultScene::Draw3D()
{
	GraphicsDevice.SetCamera(camera);
	model->Draw();
}