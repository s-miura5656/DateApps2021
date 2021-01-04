#include "PlayerUi.h"
#include "../Managers/ResouceManager/ResouceManager.h"
#include "../Data/IData.h"

SPRITE PlayerUi::score_font = nullptr;
FONT  PlayerUi::player_font = nullptr;
SPRITE PlayerUi::test       = nullptr;

PlayerUi::PlayerUi(const int player_no) : player_index(player_no)
{
	tag = PLAYER_TAG + std::to_string(player_index + 1);
}

PlayerUi::~PlayerUi()
{
}

bool PlayerUi::Initialize(LPCTSTR banner_name, const Vector3& banner_pos)
{
	banner_sprite   = ResouceManager::Instance().LordSpriteFile(banner_name);
	banner_position = banner_pos;

	if (score_font == nullptr)
		score_font = ResouceManager::Instance().LordSpriteFile(_T("NumberSprite/namber.png"));

	if(player_font == nullptr)
		player_font = GraphicsDevice.CreateSpriteFont(_T("チェックアンドU-Foフォント"), 30);

	if (test == nullptr)
	test = ResouceManager::Instance().LordSpriteFile(_T("HpSprite/ゲージベース2.png"));

	score = 0;
	prev_rank_point = 0;
	get_point = 0;
	return true;
}

int PlayerUi::Update()
{
	auto rank_point = IPrayerData::GetRankingPoint(tag);
	if (score < rank_point)
	{
		score++;
	}

	auto player_num = GraphicsDevice.WorldToScreen(IPrayerData::GetPosition(tag));
	player_num.z = SpriteBatch_TopMost;
	player_position.x = player_num.x;
	player_position.y = player_num.y;


	std::string& arm_tag = ARM_TAG + std::to_string(player_index + 1);
	Vector3 _hit = IArmData::GetHitPosition(arm_tag);

	if(rank_point > prev_rank_point)
	{
		get_point = rank_point - prev_rank_point;
		move_pos.push_back(player_num);
	}

	//! 入手ポイントの移動（ベジェにしろ）
	for (int i = 0; i < move_pos.size(); ++i)
	{
		if (move_pos[i].y != banner_position.y) {
			move_pos[i].y -= 6.0f;
		}
		if (move_pos[i].x >= banner_position.x) {
			move_pos[i].x -= 3.0f;
		}
		if (move_pos[i] == banner_position)
			move_pos.erase(move_pos.begin() + i);
	}

	prev_rank_point = rank_point;

    return 0;
}

void PlayerUi::Draw2D()
{
	SpriteBatch.Draw(*banner_sprite, banner_position);
	
	for (int i = 0; i < move_pos.size(); i++)
	{
		if (get_point <= 10) {
			SpriteBatch.Draw(*score_font, move_pos[i] + Vector3((10 * 0.25), -25, 0), RectWH((int)((get_point % 1000) % 100 / 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
			SpriteBatch.Draw(*score_font, move_pos[i] + Vector3((74 * 0.25), -25, 0), RectWH((int)((get_point % 1000) % 100 % 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
		}
		else if (get_point <= 100) {
			SpriteBatch.Draw(*score_font, move_pos[i] + Vector3(( 10 * 0.25), -25, 0), RectWH((int)((get_point % 1000) / 100)      * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
			SpriteBatch.Draw(*score_font, move_pos[i] + Vector3(( 74 * 0.25), -25, 0), RectWH((int)((get_point % 1000) % 100 / 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
			SpriteBatch.Draw(*score_font, move_pos[i] + Vector3((138 * 0.25), -25, 0), RectWH((int)((get_point % 1000) % 100 % 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
		}
		else if (get_point <= 1000) {
			SpriteBatch.Draw(*score_font, move_pos[i] + Vector3(( 10 * 0.25), -25, 0), RectWH((int)(get_point / 1000)              * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
			SpriteBatch.Draw(*score_font, move_pos[i] + Vector3(( 74 * 0.25), -25, 0), RectWH((int)((get_point % 1000) / 100)      * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
			SpriteBatch.Draw(*score_font, move_pos[i] + Vector3((138 * 0.25), -25, 0), RectWH((int)((get_point % 1000) % 100 / 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
			SpriteBatch.Draw(*score_font, move_pos[i] + Vector3((204 * 0.25), -25, 0), RectWH((int)((get_point % 1000) % 100 % 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
		}
	}

	//バナースコアアニメーション
	SpriteBatch.Draw(*score_font, banner_position + Vector3((10 * 0.3) + 90, 10, -1), RectWH((int)(score / 1000)               * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);
	SpriteBatch.Draw(*score_font, banner_position + Vector3((74 * 0.3) + 90, 10, -1), RectWH((int)((score % 1000) / 100)       * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);
	SpriteBatch.Draw(*score_font, banner_position + Vector3((138 * 0.3) + 90, 10, -1), RectWH((int)((score % 1000) % 100 / 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);
	SpriteBatch.Draw(*score_font, banner_position + Vector3((204 * 0.3) + 90, 10, -1), RectWH((int)((score % 1000) % 100 % 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);

	SpriteBatch.DrawString(player_font, player_position, Color(0.f, 0.f, 0.f), _T("%dP"), player_index + 1);
}

