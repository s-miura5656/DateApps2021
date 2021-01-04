#include "PlayerUi.h"
#include "../../Managers/ResouceManager/ResouceManager.h"

SPRITE PlayerUi::score_font = nullptr;
FONT  PlayerUi::player_font = nullptr;
SPRITE PlayerUi::test       = nullptr;

PlayerUi::PlayerUi(const int player_no) : player_index(player_no)
{
	tag		 = PLAYER_TAG + std::to_string(player_index + 1);
	_arm_tag = ARM_TAG + std::to_string(player_index + 1);

	_i_player_data = std::make_unique<IPrayerData>();
	_i_arm_data	   = std::make_unique<IArmData>();
}

PlayerUi::~PlayerUi()
{
	_i_player_data.reset();
	_i_arm_data.reset();
}

bool PlayerUi::Initialize(LPCTSTR banner_name, const Vector3& banner_pos)
{
	banner_sprite = ResouceManager::Instance().LordSpriteFile(banner_name);
	
	banner_position = banner_pos;

	if (score_font == nullptr)
		score_font = ResouceManager::Instance().LordSpriteFile(_T("NumberSprite/namber.png"));

	if(player_font == nullptr)
		player_font = ResouceManager::Instance().LordFontFile(_T("�`�F�b�N�A���hU-Fo�t�H���g"), 30);

	if (test == nullptr)
		test = ResouceManager::Instance().LordSpriteFile(_T("HpSprite/�Q�[�W�x�[�X2.png"));

	score = 0;

	return true;
}

int PlayerUi::Update()
{
	auto rank_point = _i_player_data->GetRankingPoint(tag);
	
	if (score < rank_point) {
		score++;
	}

	auto player_num = GraphicsDevice.WorldToScreen(_i_player_data->GetPosition(tag));
	player_num.z = SpriteBatch_TopMost;
	player_position.x = player_num.x;
	player_position.y = player_num.y;

	Vector3 _hit = _i_arm_data->GetHitPosition(_arm_tag);

	//!�@�A�[���̃|�W�V������������ԂłȂ��Ƃ��i�A�[�����v���C���[�Ƀq�b�g�������ɍX�V�����j
	if (_hit != Vector3_Zero)
	{
		move_pos.push_back(_hit);
//		_i_player_data->SetPosition(tag, Vector3_Zero);
	}

	for (int i = 0; i < move_pos.size(); ++i)
	{
		move_pos[i].y -= 1.0f;

		if (move_pos[i].y <= 0.0f)
			move_pos.erase(move_pos.begin() + i);
	}

    return 0;
}

void PlayerUi::Draw2D()
{
	SpriteBatch.Draw(*banner_sprite, banner_position);

	for (int i = 0; i < (move_pos.size() > 0) ? 1 : 0; i++)
	{
		//SpriteBatch.Draw(*test, move_pos[i]);
	}

	//�X�R�A�A�j���[�V����
	SpriteBatch.Draw(*score_font, banner_position + Vector3((10 * 0.3) + 90, 10, -1), RectWH((int)(score / 1000) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);
	SpriteBatch.Draw(*score_font, banner_position + Vector3((74 * 0.3) + 90, 10, -1), RectWH((int)((score % 1000) / 100) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);
	SpriteBatch.Draw(*score_font, banner_position + Vector3((138 * 0.3) + 90, 10, -1), RectWH((int)((score % 1000) % 100 / 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);
	SpriteBatch.Draw(*score_font, banner_position + Vector3((204 * 0.3) + 90, 10, -1), RectWH((int)((score % 1000) % 100 % 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);

	SpriteBatch.DrawString(player_font, player_position, Color(0.f, 0.f, 0.f), _T("%dP"), player_index + 1);
}
