#include"TitleScene.h"
#include"../../Data/WordsTable.h"
#include"../../Data/ModelAnimation.h"

/*
* @fn �^�C�g���̏�����
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
bool TitleScene::Initialize()
{
	_title = GraphicsDevice.CreateSpriteFromFile(_T("TitleSprite/Title.png"));

	ControllerManager::Instance().SetGamePadMaxCount(PLAYER_COUNT_MAX);

	ControllerManager::Instance().CreateGamePad(PLAYER_TAG + std::to_string(1));

	for (int i = 0; i < 4; i++)
	{
		model[i] = GraphicsDevice.CreateModelFromFile(_T("Player/robot.x"));
	}
	

	item = GraphicsDevice.CreateModelFromFile(_T("TitleSprite/item_04.X"));


	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f); // �A�e�̃O���f�[�V���� ���邢����
	material.Ambient = Color(1.0f, 1.0f, 1.0f); // �x�[�X�̐F�@�Â�����
	material.Specular = Color(1.0f, 1.0f, 1.0f); // �e�J��
	material.Power = 10.0f; // �e�J���̌��ʂ̋���

	for (int i = 0; i < 4; i++)
	{
		model[i]->SetMaterial(material);
		model[i]->SetPosition(Vector3(-4 + 3* i, 0, 0));
		model[i]->SetRotation(90, 0, 0);
		model[i]->SetScale(1.0f, 1.0f, 1.0f);
	}

	item->SetMaterial(material);
	item->SetScale(5.0f, 5.0f, 5.0f);
	item->SetRotation(270, 0, 0);
	

	camera->SetView(Vector3(0, 0, 0), Vector3(5, 0, 0)); // ���_
	camera->SetPerspectiveFieldOfView(45.0f, 16.0f / 9.0f, 1.0f, 10000.0f); // ���E

	
	GraphicsDevice.SetCamera(camera);

	return true;
}
/*
* @fn �^�C�g���̍X�V
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
int TitleScene::Update()
{
	auto pad = ControllerManager::Instance().GetController(PLAYER_TAG + std::to_string(1));
	
	if (pad->GetButtonBuffer(GamePad_Button1))
	{
		//exit(0);
	}


	// ���f���̉�]
	ModelRotation(Vector3(0.0f, 0.0f, 5.0f), model[0]);
	ModelRotation(Vector3(0.0f, 3.0f, 0.0f), item);

	// ���f���̊g��k��
	_scale = ModelScaling(5.f, 1.f, _scale, 0.05f, model[1]);
	model[1]->SetScale(Vector3_One * _scale);

	// ���f���̓_��
	_alpha = ModelFlashing(1.0f, 0.0f, _alpha, 0.1f, model[2]);
	_alpha = ModelFlashing(1.0f, 0.0f, _alpha, 0.1f, item);

	// ���f����Z������
	_bound = ModelBound(_bound, 0.0f, 5.0f, 2.0f, model[3]);

	return 0;
}

/*
* @fn �^�C�g���̕`��
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
void TitleScene::Draw2D()
{
	//SpriteBatch.Draw(*_title, Vector3(0, 0, +10000.0f));
}
void TitleScene::Draw3D()
{
	//item->Draw();

	model[0]-> Draw();
	model[1]->Draw();
	model[3]->Draw();

	GraphicsDevice.BeginAlphaBlend();
	model[2]->DrawAlpha(_alpha);
	item->DrawAlpha(_alpha);
	GraphicsDevice.EndAlphaBlend();

	GraphicsDevice.SetCamera(camera);
}

