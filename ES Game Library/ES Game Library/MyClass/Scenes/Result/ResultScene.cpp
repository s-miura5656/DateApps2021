#include"ResultScene.h"
#include"../../Data/WordsTable.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include "../../Data/MyAlgorithm.h"
ResultScene::ResultScene()
{

}
ResultScene::~ResultScene()
{

}
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
	model = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	txt = ResouceManager::Instance().LordFontFile(_T("Yu Gothic UI"), 70);

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

	_i_player_data = new IPrayerData;

	auto data = SceneManager::Instance().GetResultData();

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);
		if (_i_player_data->GetRankNum(tag) == 0)
		{
			num = _i_player_data->GetRankNum(tag) + 1;
			break;
		}
	}
	
	auto path = ConvertFilePath("Player/", data->tag, ".png");
	_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());

	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/CharaShader.hlsl"));
	model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");
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
	auto data = SceneManager::Instance().GetResultData();

	SpriteBatch.Draw(*ground, Vector3(0,0,10000));
	SpriteBatch.Draw(*champion, Vector3(800,50,0));
	SpriteBatch.Draw(*totitle, Vector3(800, 600, 0));

	if (data->tag == PLAYER_TAG + "1")
	{
		SpriteBatch.DrawString(txt, Vector2(700, 100), Color(255, 255, 0), _T("�`�����s�I����PLAYER_1�ł�"));
	}
	else if (data->tag == PLAYER_TAG + "2")
	{
		SpriteBatch.DrawString(txt, Vector2(700, 100), Color(255, 255, 0), _T("�`�����s�I����PLAYER_2�ł�"));
	}
	else if (data->tag == PLAYER_TAG + "3")
	{
		SpriteBatch.DrawString(txt, Vector2(700, 100), Color(255, 255, 0), _T("�`�����s�I����PLAYER_3�ł�"));
	}
	else if (data->tag == PLAYER_TAG + "4")
	{
		SpriteBatch.DrawString(txt, Vector2(700, 100), Color(255, 255, 0), _T("�`�����s�I����PLAYER_4�ł�"));
	}
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		SpriteBatch.DrawString(txt, Vector2(750, 150 + 50 * i), Color(255, 255, 0), _T("Player_%d"),i + 1);
		SpriteBatch.DrawString(txt, Vector2(950, 150 + 50 * i), Color(255, 255, 0), _T("POINT::%d"),data->points[i]);
	}
}
void ResultScene::Draw3D()
{
	Matrix vp = camera->GetViewProjectionMatrix();
	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetTechnique("FixModel");
	_shader->SetParameter("vp", vp);
	GraphicsDevice.SetCamera(camera);
	model->Draw(_shader);
}