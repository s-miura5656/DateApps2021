#include"ResultScene.h"
#include"../../Data/WordsTable.h"
#include"../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include "../../Managers/InputManager/InputManager.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Data/IData.h"

ResultScene::ResultScene()
{

}

ResultScene::~ResultScene()
{

}

/*
* @fn ���U���g�̏�����
*/
bool ResultScene::Initialize()
{
	ArrivalCount();

	//! file
	_player_rank_num = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/number.png"));
	_background		 = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/ground.png"));
	_totitle	     = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/button.png"));
	_font			 = ResouceManager::Instance().LordFontFile(_T("�`�F�b�N�A���hU-Fo�t�H���g"), 100);
	_shader			 = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	_player_model	 = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));

	_player_model->SetRotation(0, 180, 0);
	_player_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//�v���C���[���ƂɃe�N�X�`����p�ӂ���B
		auto path = ConvertFilePath("Player/", PLAYER_TAG + std::to_string(GetRankNum(i)), ".png");
		SPRITE texture = ResouceManager::Instance().LordSpriteFile(path.c_str());
		_texture.push_back(texture);
	}

	//! material
	Material material;
	material.Diffuse  = Color(1.0f, 1.0f, 1.0f); // �A�e�̃O���f�[�V���� ���邢����
	material.Ambient  = Color(1.0f, 1.0f, 1.0f); // �x�[�X�̐F�@�Â�����
	material.Specular = Color(1.0f, 1.0f, 1.0f); // �e�J��
	material.Power    = 10.0f;                   // �e�J���̌��ʂ̋���

	_player_model->SetMaterial(material);

	//! camera
	Viewport view       = GraphicsDevice.GetViewport();
	Vector3 _camera_pos = Vector3(0, 0, -10);
	Vector3 _look_pos   = Vector3_Zero;

	SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(60.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	//!�v���C���[���f���̃X�P�[���̐ݒ�
	_player_model_big_scale   = 1.0;
	_player_model_small_scale = 0.5;

	//!�v���C���[��Y���W�̈ʒu����C��
	_player_big_position_x   = 0.8;
	_player_small_position_x = 1.2;

	//!�v���C���[�̏��ʂ̍��W�̐ݒ�
	_player_rank_number_position_x = -15;
	_player_rank_number_position_y = -50;

	//!�|�C���g�̏��ʂ�X���W�̈ʒu����C��
	_point_small_text_position_x = 300;
	_point_big_text_position_x   = 330;

	//!�|�C���g�̃e�L�X�g�̃X�P�[���̐ݒ�
	_text_small_size = Vector2(1.0, 1.0);
	_text_big_size   = Vector2(0.5, 0.5);

	//!�|�C���g�̏��ʂ̍��W�̐ݒ�
	_point_big_text_position       = Vector2(110, 550);
	_point_small_text_position     = Vector2(150, 500);

	//!�v���C���[�̍��W�̐ݒ�
	_player_big_position   = Vector3(-1.5, 0, -7.5);
	_player_small_position = Vector3(-1.8, 0, -7.5);

	//�w�i�̍��W
	_background_position = Vector3(0, 0, 10000);
	//�V�[���J�ڂ̕��@�̍��W
	_totitle_position    = Vector3(900, 600, 0);

	return true;
}

/*
* @fn ���U���g�̍X�V
*/
int ResultScene::Update()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		auto pad = InputManager::Instance().GetGamePad(PLAYER_TAG + std::to_string(i + 1));
		pad->Refresh();
		//�p���`���o���{�^���������ꂽ�Ƃ��Ƀ^�C�g���փV�[���J�ڂ���B
		if (pad->ButtonDown(BUTTON_INFO::BUTTON_B))
		{
			SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::TITLE);
		}
	}
	return 0;
}

/*
* @fn ���U���g��2D�`��
*/
void ResultScene::Draw2D()
{
	SpriteBatch.Draw(*_background,_background_position);

	SpriteBatch.Draw(*_totitle,_totitle_position);
	
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		SpriteBatch.DrawString(_font, PointTextPosition(i), Color(255, 0, 0), _T("%d"), GetPoints(i));
		SpriteBatch.Draw(*_player_rank_num, PlayerRankNumberPositionCalculation(i) + Vector3(0,-50,0), 
			RectWH((GetRankNum(i) - 1) * 128, 0, 128, 64), 1,Vector3_Zero,Vector3_Zero, TextSizeCalculation(i));
	}
}
/*
* @fn ���U���g��3D�`��
*/
void ResultScene::Draw3D()
{
	Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
	SceneCamera::Instance().SetSceneCamera();

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		_shader->SetTexture("m_Texture", *_texture[i]);
		_shader->SetParameter("vp", vp);
		_player_model->SetScale(PlayerScaleCalculation(i));
		_player_model->SetPosition(PlayerPositionCalculation(i));
		_player_model->Draw(_shader);
	}
}
/*
* @fn �����̐��𐔂���
*/
void ResultScene::ArrivalCount()
{
	_arrival_count = 1;

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		//i�Ԗڂ̃|�C���g�Ƃ��̎��̏��ʂ̃|�C���g��������������1�ʂɂȂ�l�̃J�E���g�𑝂₷�B
		if (GetPoints(i) == GetPoints(i + 1)) {
			_arrival_count++;
		}
		else
		{
			break;
		}
	}
}
/**
 * @fn ���U���g�f�[�^���珸���Ƀv���C���[�̏��ʂ��擾����
 * @param (player_num) ���ʂ����Ԗڂ̃v���C���[��
 * @return ���U���g�f�[�^���珸���Ƀv���C���[�̏��ʂ�Ԃ�
 */
int ResultScene::GetRankNum(int player_num)
{
	auto resultdata = SceneManager::Instance().GetResultData();
	return resultdata->ranknum[player_num];
}
/**
 * @fn ���U���g�f�[�^���珸���Ƀv���C���[�̃|�C���g���擾����
 * @param (player_num) ���ʂ����Ԗڂ̃v���C���[��
 * @return ���U���g�f�[�^���珸���Ƀv���C���[�̃|�C���g��Ԃ�
 */
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

	if (player_num < _arrival_count) {
		pl_model_scale = _player_model_big_scale;
	}
	else
	{
		pl_model_scale = _player_model_small_scale;
	}

	return pl_model_scale;
}

/**
 * @brief�@�e�L�X�g�̃T�C�Y��ݒ肷��
 * @param (player_num) ���ʂ����Ԗڂ̃v���C���[��
 * @return �e�L�X�g�̃T�C�Y��Vector2�^�̒l�ŕԂ�
 */
Vector2 ResultScene::TextSizeCalculation(int player_num) 
{
	Vector2 text_size;
	
	if (player_num < _arrival_count) {
		text_size = Vector2(_text_big_size);
	}
	else
	{
		text_size = Vector2(_text_small_size);
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

	if (player_num < _arrival_count) {
		pl_pos    = _player_big_position;
		pl_pos.x += _player_big_position_x * player_num;
	}
	else
	{
		pl_pos    = _player_small_position;
		pl_pos.x += _player_small_position_x * player_num;
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

	if (player_num < _arrival_count) {
		pl_rank_pos.x = PointTextPosition(player_num).x + _player_rank_number_position_x;
		pl_rank_pos.y = PointTextPosition(player_num).y + _player_rank_number_position_y;
	}
	else 
	{
		pl_rank_pos.x = PointTextPosition(player_num).x + _player_rank_number_position_x;
		pl_rank_pos.y = PointTextPosition(player_num).y + _player_rank_number_position_y;
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

	if (player_num < _arrival_count) {
		pointpos    = _point_big_text_position;
		pointpos.x += _point_big_text_position_x * player_num;
	}
	else {
		pointpos    = _point_small_text_position;
		pointpos.x += _point_small_text_position_x * (player_num - _arrival_count + 1);
	}

	return pointpos;
}