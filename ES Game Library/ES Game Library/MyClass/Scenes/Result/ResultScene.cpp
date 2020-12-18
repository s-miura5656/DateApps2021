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
* @fn �^�C�g���̏�����
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
bool ResultScene::Initialize()
{
	AllPosCalculation();
	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f); // �A�e�̃O���f�[�V���� ���邢����
	material.Ambient = Color(1.0f, 1.0f, 1.0f); // �x�[�X�̐F�@�Â�����
	material.Specular = Color(1.0f, 1.0f, 1.0f); // �e�J��
	material.Power = 10.0f; // �e�J���̌��ʂ̋���

	player_rank_num = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/number.png"));
	background = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/ground.png"));
	totitle = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/button.png"));
	font = ResouceManager::Instance().LordFontFile(_T("�`�F�b�N�A���hU-Fo�t�H���g"), 100);
	shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	player_model = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	player_model->SetMaterial(material);
	player_model->SetRotation(0, 0, 0);
	player_model->RegisterBoneMatricesByName(shader, "WorldMatrixArray", "NumBones");

	Viewport view = GraphicsDevice.GetViewport();
	Vector3 _camera_pos = Vector3(0, 0, -10);
	Vector3 _look_pos = Vector3(0, 0, 0);

	SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(60.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	ControllerManager::Instance().CreateGamePad(PLAYER_TAG + std::to_string(1));
	ControllerManager::Instance().SetGamePadMaxCount(PLAYER_COUNT_MAX);
	return true;
}
/*
* @fn �^�C�g���̍X�V
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
int ResultScene::Update()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		auto pad = ControllerManager::Instance().GetController(PLAYER_TAG + std::to_string(i + 1));
		pad->GamePadRefresh();
		//�p���`���o���{�^���������ꂽ�Ƃ��Ƀ^�C�g���փV�[���J�ڂ���B
		if (pad->GetButtonBuffer(GamePad_Button2))
		{
			SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::TITLE);
		}
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
	auto data = SceneManager::Instance().GetResultData();
	SpriteBatch.Draw(*background, Vector3(0, 0, 10000));
	SpriteBatch.Draw(*totitle, Vector3(900, 600, 0));
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		SpriteBatch.DrawString(font, Vector2(point_text_position[i]), Color(255, 0, 0), _T("%d"), data->points[i]);
		SpriteBatch.Draw(*player_rank_num, Vector3(player_rank_num_position[i]) + Vector3(0,-50,0), RectWH((data->ranknum[i] - 1) * 128, 0, 128, 64), 1, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector2(TextSizeCalculation(i)));
	}
}
void ResultScene::Draw3D()
{
	Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
	SceneCamera::Instance().SetSceneCamera();
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		shader->SetTexture("m_Texture", *texture[i]);
		shader->SetParameter("vp", vp);
		player_model->SetScale(PlayerScaleCalculation(i));
		player_model->SetPosition(PlayerPositionCalculation(i));
		player_model->Draw(shader);
	}
}
void ResultScene::AllPosCalculation()
{
	i_player_data = new IPrayerData;
	auto resultdata = SceneManager::Instance().GetResultData();

	arrival_count = 1;
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//i�Ԗڂ̃|�C���g�Ƃ��̎��̏��ʂ̃|�C���g��������������1�ʂɂȂ�l�̃J�E���g�𑝂₷�B
		if (resultdata->points[i] == resultdata->points[i + 1]) {
			arrival_count++;
		}
		else
		{
			break;
		}
	}
	int point_text_fix[PLAYER_COUNT_MAX] = {};
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//�v���C���[���ƂɃe�N�X�`����p�ӂ���B
		auto path = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(resultdata->ranknum[i]), ".png");
		SPRITE _texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
		texture.push_back(_texture);
		//�|�C���g�̌����ɂ���Ĉʒu���C������B
		if (resultdata->points[0] >= 10 * (10 * i)) {
			point_text_fix[i] = 30 - 30 * i;
		}
	}
	int first_rank_ui_pos_x;
	for (int i = 0; i < arrival_count; i++)
	{
		first_rank_ui_pos_x = 80 + 300 * i + point_text_fix[i];
		point_text_position.push_back(Vector2(first_rank_ui_pos_x, 550));
		player_rank_num_position.push_back(Vector3(first_rank_ui_pos_x, 450, 0));
	}
	int count = 0;
	for (int i = arrival_count; i < PLAYER_COUNT_MAX; i++)
	{
		point_text_position.push_back(Vector2(first_rank_ui_pos_x + 330 + 330 * count, 500));
		player_rank_num_position.push_back(Vector3(first_rank_ui_pos_x + 330 * i, 460, 0));
		count++;
	}
}
float ResultScene::PlayerScaleCalculation(int num)
{
	float scale;
	if (num < arrival_count) {
		scale = 1.0;
	}
	else
	{
		scale = 0.5;
	}
	return scale;
}
Vector2 ResultScene::TextSizeCalculation(int num) {
	Vector2 size;
	if (num < arrival_count) {
		size = Vector2(1.0,1.0);
	}
	else
	{
		size = Vector2(0.5, 0.5);
	}
	return size;
}
Vector3 ResultScene::PlayerPositionCalculation(int num) 
{
	Vector3 pos;
	if (num < arrival_count) {
		pos = Vector3(-1.5 + (0.8 * num), 0, -7.5);
	}
	else
	{
		pos = Vector3(-1.8 + (1.2 * num), 0, -7.5);
	}
	return pos;
}