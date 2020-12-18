#include"ResultScene.h"
#include"../../Data/WordsTable.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Data/IData.h"

ResultScene::ResultScene()
{
	i_player_data = new IPrayerData;
}
ResultScene::~ResultScene()
{
	delete i_player_data;
}
/*
* @fn �^�C�g���̏�����
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
bool ResultScene::Initialize()
{
	ArrivalCount();
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

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//�v���C���[���ƂɃe�N�X�`����p�ӂ���B
		auto path = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(GetRankNum(i)), ".png");
		SPRITE _texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
		texture.push_back(_texture);
	}

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
	SpriteBatch.Draw(*background, Vector3(0, 0, 10000));
	SpriteBatch.Draw(*totitle, Vector3(900, 600, 0));
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		SpriteBatch.DrawString(font, Vector2(PointTextPosition(i)), Color(255, 0, 0), _T("%d"), GetPoints(i));
		SpriteBatch.Draw(*player_rank_num, Vector3(PlayerRankNumberPositionCalculation(i)) + Vector3(0,-50,0), RectWH((GetRankNum(i) - 1) * 128, 0, 128, 64), 1, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector2(TextSizeCalculation(i)));
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
void ResultScene::ArrivalCount()
{
	arrival_count = 1;
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//i�Ԗڂ̃|�C���g�Ƃ��̎��̏��ʂ̃|�C���g��������������1�ʂɂȂ�l�̃J�E���g�𑝂₷�B
		if (GetPoints(i) == GetPoints(i) + 1) {
			arrival_count++;
		}
		else
		{
			break;
		}
	}
}
int ResultScene::GetRankNum(int player_num)
{
	auto resultdata = SceneManager::Instance().GetResultData();
	return resultdata->ranknum[player_num];
}
int ResultScene::GetPoints(int player_num)
{
	auto resultdata = SceneManager::Instance().GetResultData();
	return resultdata->points[player_num];
}
/**
 * @brief�@�v���C���[���f���̃X�P�[����ݒ肷��
 * @param (player_num) ���ʂ����Ԗڂ̃v���C���[��
 * @return �v���C���[�̃X�P�[���ɃZ�b�g����float�^�̒l�ŕԂ�
 */
float ResultScene::PlayerScaleCalculation(int player_num)
{
	float pl_model_scale;
	if (player_num < arrival_count) {
		pl_model_scale = 1.0;
	}
	else
	{
		pl_model_scale = 0.5;
	}
	return pl_model_scale;
}
/**
 * @brief�@�e�L�X�g�̃T�C�Y��ݒ肷��
 * @param (player_num) ���ʂ����Ԗڂ̃v���C���[��
 * @return �e�L�X�g�̃T�C�Y��Vector2�^�̒l�ŕԂ�
 */
Vector2 ResultScene::TextSizeCalculation(int player_num) {
	Vector2 text_size;
	if (player_num < arrival_count) {
		text_size = Vector2(1.0,1.0);
	}
	else
	{
		text_size = Vector2(0.5, 0.5);
	}
	return text_size;
}
/**
 * @brief�@�v���C���[�̍��W��ݒ肷��
 * @param (player_num) ���ʂ����Ԗڂ̃v���C���[��
 * @return �v���C���[�̍��W��Vector3�^�̒l�ŕԂ�
 */
Vector3 ResultScene::PlayerPositionCalculation(int player_num)
{
	Vector3 pl_pos;
	if (player_num < arrival_count) {
		pl_pos = Vector3(-1.5 + (0.8 * player_num), 0, -7.5);
	}
	else
	{
		pl_pos = Vector3(-1.8 + (1.2 * player_num), 0, -7.5);
	}
	return pl_pos;
}
/**
 * @brief�@�v���C���[�̍��W��ݒ肷��
 * @param (player_num) ���ʂ����Ԗڂ̃v���C���[��
 * @return �v���C���[�̍��W��Vector3�^�̒l�ŕԂ�
 */
Vector3 ResultScene::PlayerRankNumberPositionCalculation(int player_num)
{
	Vector3 pl_rank_pos = (Vector3_Zero);
	if (player_num < arrival_count) {
		pl_rank_pos.x = PointTextPosition(player_num).x - 15;
		pl_rank_pos.y = PointTextPosition(player_num).y + -50;
	}
	else 
	{
		pl_rank_pos.x = PointTextPosition(player_num).x - 15;
		pl_rank_pos.y = PointTextPosition(player_num).y + -50;
	}
	return pl_rank_pos;
}
/**
 * @brief�@�|�C���g�̍��W��ݒ肷��
 * @param (player_num) ���ʂ����Ԗڂ̃v���C���[��
 * @return �|�C���g�̍��W��Vector2�^�̒l�ŕԂ�
 */
Vector2 ResultScene::PointTextPosition(int player_num)
{
	Vector2 pointpos;
	if (player_num < arrival_count) {
		pointpos = Vector2(110 + 300 * player_num,550);
	}
	else {
		pointpos = Vector2(150 + (330 * (player_num - arrival_count + 1)), 500);
	}
	return pointpos;
}