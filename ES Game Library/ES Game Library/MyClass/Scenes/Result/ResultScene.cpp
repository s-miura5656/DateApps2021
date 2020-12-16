#include"ResultScene.h"
#include"../../Data/WordsTable.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Data/IData.h"

ResultScene::ResultScene()
{

}
ResultScene::~ResultScene()
{

}
/*
* @fn タイトルの初期化
* @param　なし
* @return　なし
*/
bool ResultScene::Initialize()
{
	player = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/number.png"));
	ground = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/ground.png"));
	totitle = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/button.png"));
	model = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	txt = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 70);
	auto _effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/effekseer_break02/break_effect.efk"));

	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f); // 陰影のグラデーション 明るい部分
	material.Ambient = Color(1.0f, 1.0f, 1.0f); // ベースの色　暗い部分
	material.Specular = Color(1.0f, 1.0f, 1.0f); // テカリ
	material.Power = 10.0f; // テカリの効果の強さ

	model->SetMaterial(material);
	model->SetPosition(Vector3(-1, -0.5, 0));
	model->SetRotation(0, 0, 0);
	model->SetScale(1.5f);

	auto data = SceneManager::Instance().GetResultData();

	auto path = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(data->ranknum[0]), ".png");
	_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());

	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");

	Viewport view = GraphicsDevice.GetViewport();
	Vector3 _camera_pos = Vector3(0, 0, -10);
	Vector3 _look_pos = Vector3(0, 0, 0);

	SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(60.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);
	SceneCamera::Instance().SetSceneCamera();

	return true;
}
/*
* @fn タイトルの更新
* @param　なし
* @return　なし
*/
int ResultScene::Update()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		auto pad = ControllerManager::Instance().GetController(PLAYER_TAG + std::to_string(i + 1));
		pad->GamePadRefresh();

		if (pad->GetButtonBuffer(GamePad_Button2))
		{
			SceneManager::Instance().ChangeScene(SceneManager::TITLE);
		}
	}
	return 0;
}

/*
* @fn タイトルの描画
* @param　なし
* @return　なし
*/
void ResultScene::Draw2D()
{
	auto data = SceneManager::Instance().GetResultData();
	SpriteBatch.Draw(*ground, Vector3(0,0,10000));
	SpriteBatch.Draw(*totitle, Vector3(900, 600, 0));

	SpriteBatch.DrawString(txt, Vector2(960, 150), Color(255, 0, 0),_T("%d"), data->points[0]);
	SpriteBatch.Draw(*player, Vector3(750, 130,0), RectWH((data->ranknum[0] - 1), 0, 128, 64),1,Vector3(0, 0, 0), Vector3(0, 0, 0), Vector2(1.5f, 1.5f));
	
	for (int i = 1; i < PLAYER_COUNT_MAX; i++)
	{
		SpriteBatch.DrawString(txt, Vector2(960, 150 + (105 * i)), Color(0, 0, 0), _T("%d"), data->points[i]);
		SpriteBatch.Draw(*player, Vector3(750 - 30 * i, 150 + (100 * i), 0), RectWH((data->ranknum[i] - 1) * 128, 0, 128, 64));
	}
}
void ResultScene::Draw3D()
{
	//model->SetTrackPosition(1, GameTimer.GetElapsedSecond() * 2.0f);
	//model->SetTrackEnable(0, TRUE);

	Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetTechnique("FixModel");
	_shader->SetParameter("vp", vp);
	model->SetPosition(Vector3(-1.0f, -0.8f, -7.5f));
	model->Draw(_shader);
}