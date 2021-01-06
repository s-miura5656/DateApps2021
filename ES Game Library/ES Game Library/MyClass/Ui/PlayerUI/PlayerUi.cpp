#include "PlayerUi.h"
#include "../../Managers/ResouceManager/ResouceManager.h"

SPRITE PlayerUi::score_font = nullptr;
FONT  PlayerUi::player_font = nullptr;

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
		player_font = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 30);

	score = 0;
	prev_rank_point = 0;
	corner[0] = Vector3( 640,   0, 0);
	corner[1] = Vector3( 640, 720, 0);
	
	add_point = 0;
	delta_point = 0;

	return true;
}

int PlayerUi::Update()
{
	auto rank_point = _i_player_data->GetRankingPoint(tag);

	//! 配列のerase時と今のスコア比較
	if (score < add_point)
	{
		score += delta_point;
		if (score > add_point)
			score = add_point;
	}

	//! 配列のerase時と今のスコア比較
	if (score > rank_point)
	{
		score = rank_point;
		add_point = rank_point;
	}
		auto player_num = GraphicsDevice.WorldToScreen(_i_player_data->GetPosition(tag));
		player_num.z = SpriteBatch_TopMost;
		player_position.x = player_num.x;
		player_position.y = player_num.y;

		std::string& arm_tag = ARM_TAG + std::to_string(player_index + 1);
		Vector3 _hit = _i_arm_data->GetHitPosition(arm_tag);

	RegisterPointAnimation(player_num);
	MovePointAnimation(player_num);
	
    return 0;
}

void PlayerUi::Draw2D()
{
	SpriteBatch.Draw(*banner_sprite, banner_position);

	//! 入手ポイントのアニメーション
	for (int i = 0; i < pointAnimation.size(); i++)
	{
		if (pointAnimation[i].point >= 100) {
			SpriteBatch.Draw(*score_font, pointAnimation[i].position + Vector3((10 * 0.25), -25, 0), RectWH((int)(pointAnimation[i].point / 100) * 64, 0, 64, 64), pointAnimation[i].alpha, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
			SpriteBatch.Draw(*score_font, pointAnimation[i].position + Vector3((74 * 0.25), -25, 0), RectWH((int)((pointAnimation[i].point % 100) / 10) * 64, 0, 64, 64), pointAnimation[i].alpha, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
			SpriteBatch.Draw(*score_font, pointAnimation[i].position + Vector3((138 * 0.25), -25, 0), RectWH((int)((pointAnimation[i].point % 100) % 10) * 64, 0, 64, 64), pointAnimation[i].alpha, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
		}
		/*else if (pointAnimation[i].point <= 1000) {
			SpriteBatch.Draw(*score_font, pointAnimation[i].position + Vector3(( 10 * 0.25), -25, 0), RectWH((int)(pointAnimation[i].point / 1000)              * 64, 0, 64, 64), pointAnimation[i].alpha, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
			SpriteBatch.Draw(*score_font, pointAnimation[i].position + Vector3(( 74 * 0.25), -25, 0), RectWH((int)((pointAnimation[i].point % 1000) / 100)      * 64, 0, 64, 64), pointAnimation[i].alpha, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
			SpriteBatch.Draw(*score_font, pointAnimation[i].position + Vector3((138 * 0.25), -25, 0), RectWH((int)((pointAnimation[i].point % 1000) % 100 / 10) * 64, 0, 64, 64), pointAnimation[i].alpha, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);
			SpriteBatch.Draw(*score_font, pointAnimation[i].position + Vector3((204 * 0.25), -25, 0), RectWH((int)((pointAnimation[i].point % 1000) % 100 % 10) * 64, 0, 64, 64), pointAnimation[i].alpha, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.25f);*/

	}

	//バナースコアアニメーション
	SpriteBatch.Draw(*score_font, banner_position + Vector3((10 * 0.3) + 90, 10, -1), RectWH((int)(score / 1000) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);
	SpriteBatch.Draw(*score_font, banner_position + Vector3((74 * 0.3) + 90, 10, -1), RectWH((int)((score % 1000) / 100) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);
	SpriteBatch.Draw(*score_font, banner_position + Vector3((138 * 0.3) + 90, 10, -1), RectWH((int)((score % 1000) % 100 / 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);
	SpriteBatch.Draw(*score_font, banner_position + Vector3((204 * 0.3) + 90, 10, -1), RectWH((int)((score % 1000) % 100 % 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);

	SpriteBatch.DrawString(player_font, player_position, Color(0.f, 0.f, 0.f), _T("%dP"), player_index + 1);

	if      (_i_player_data->GetParameterLevel(tag) == 1) 
	{
		SpriteBatch.Draw(*score_font, banner_position + Vector3((10 * 0.3), -30, 0), RectWH(_i_player_data->GetParameterLevel(tag) * 64, 0, 64, 64), Color(1.f, 1.f, 1.f), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);
	}
	else if (_i_player_data->GetParameterLevel(tag) == 2) 
	{
		SpriteBatch.Draw(*score_font, banner_position + Vector3((10 * 0.35), -30, 0), RectWH(_i_player_data->GetParameterLevel(tag) * 64, 0, 64, 64), Color(1.f, 1.f, 1.f), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.35f);
	}
	else if (_i_player_data->GetParameterLevel(tag) == 3) 
	{
		SpriteBatch.Draw(*score_font, banner_position + Vector3((10 * 0.4), -30, 0), RectWH(_i_player_data->GetParameterLevel(tag) * 64, 0, 64, 64), Color(1.f, 1.f, 1.f), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.4f);
	}
	else if (_i_player_data->GetParameterLevel(tag) == 4) 
	{
		SpriteBatch.Draw(*score_font, banner_position + Vector3((10 * 0.5), -30, 0), RectWH(_i_player_data->GetParameterLevel(tag) * 64, 0, 64, 64), Color(1.f, 1.f, 1.f), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.5f);
	}
}

void PlayerUi::RegisterPointAnimation(Vector3 player_num)
{
	auto rank_point = _i_player_data->GetRankingPoint(tag);

	//! ポイントを入手した時
	if (rank_point > prev_rank_point)
	{
		auto pointAnim = PointAnimation();
		pointAnim.point = rank_point - prev_rank_point;
		pointAnim.position = player_num;
		pointAnim.theta = 0.0f;
		pointAnim.alpha = 1.0f;
		pointAnimation.push_back(pointAnim);
	}
	prev_rank_point = rank_point;
}

void PlayerUi::MovePointAnimation(Vector3 player_num)
{

	//! 入手ポイントの移動
	for (int i = 0; i < pointAnimation.size(); ++i)
	{
		Vector3 bezier  = Vector3_Bezier(player_num, corner[0], corner[0], banner_position + Vector3(100, 40, 0), pointAnimation[i].theta);
		Vector3 bezier2 = Vector3_Bezier(player_num, corner[1], corner[1], banner_position + Vector3(  0, 0, 0), pointAnimation[i].theta);
		pointAnimation[i].theta += 0.008;

		//! 1pと2pのベジェ曲線
		if (player_index == 0 || player_index == 1) {
			pointAnimation[i].position.y = bezier.y;
			pointAnimation[i].position.x = bezier.x;
		}

		//! 3pと4pのベジェ曲線
		if (player_index == 2 || player_index == 3) {
			pointAnimation[i].position.y = bezier2.y;
			pointAnimation[i].position.x = bezier2.x;
		}

		pointAnimation[i].alpha -= 0.003;

		//! バナーの座標に入手したポイントがたどり着いたとき 1p & 3p
		if (player_index == 0 || player_index == 2) {
			if (pointAnimation[i].position.x <= banner_position.x + 100) {
				add_point += pointAnimation[i].point;
				delta_point = (add_point - score) / GameTimer.GetFPS() * 1;
				pointAnimation.erase(pointAnimation.begin() + i);
			}
		}

		//! バナーの座標に入手したポイントがたどり着いたとき 2p & 4p
		if (player_index == 1 || player_index == 3) {
			if (pointAnimation[i].position.x >= banner_position.x + 100) {
				add_point += pointAnimation[i].point;
				delta_point = (add_point - score) / GameTimer.GetFPS() * 1;
				pointAnimation.erase(pointAnimation.begin() + i);
			}
		}
	}
}

