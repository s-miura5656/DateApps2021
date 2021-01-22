#include "PlayerUi.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include "../../Managers/SceneManager/SceneManager.h"
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

bool PlayerUi::Initialize(const Vector3& banner_pos, RectWH banner_rectWH)
{
	banner_sprite = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/score_0110.png"));
	banner_position = banner_pos;
	banner_rw = banner_rectWH;
	banner_status = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/status.png"));
	item_icon = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/item_.png"));
	joy_icon = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/player0122.png"));
	normal_icon = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/icon02_.png"));

	ranking = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/runking.png"));

	if (score_font == nullptr)
		score_font = ResouceManager::Instance().LordSpriteFile(_T("NumberSprite/namber.png"));

	if(player_font == nullptr)
		player_font = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"),2);

	score = 0;
	prev_rank_point = 0;
	corner[0] = Vector3( 640,   0, 0);
	corner[1] = Vector3( 640, 720, 0);
	
	add_point = 0;
	delta_point = 0;
	lost_point = 0;
	lost_flag = false;

	ranking_timer = 10;

	player_pos = Vector3_Zero;
	
	return true;
}

int PlayerUi::Update()
{
	auto rank_point = _i_player_data->GetRankingPoint(tag);
	auto player_num = GraphicsDevice.WorldToScreen(_i_player_data->GetPosition(tag));

	

	auto normal_param = _i_player_data->GetAllParametor();
	auto pram_up = _i_player_data->GetStatusTag(tag);
	//auto param_down = _i_player_data->GetParameter_PowerDown(tag);

		player_num.z = SpriteBatch_TopMost;
		player_position.x = player_num.x;
		player_position.y = player_num.y;

		player_pos.x = player_num.x;
		player_pos.y = player_num.y;
		
		std::string& arm_tag = ARM_TAG + std::to_string(player_index + 1);
		Vector3 _hit = _i_arm_data->GetHitPosition(arm_tag);

	RegisterPointAnimation(player_num);
	MovePointAnimation(player_num);

	//! 配列のerase時と今のスコア比較
	if (score < add_point)
	{
		score += delta_point;
		if (score > add_point)
			score = add_point;
	}
	else
	{
		_font_size = 0.6;
	}

	//! 配列のerase時と今のスコア比較
	if (score > rank_point)
	{
		score -= 10;
		add_point = rank_point;
	}

    return 0;
}

void PlayerUi::Draw2D()
{
	SpriteBatch.Draw(*banner_sprite, banner_position, banner_rw);
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);
		if (name == tag)
		{
			SpriteBatch.Draw(*banner_status, banner_position + Vector3(0, 74, 0), RectWH(256 * (SceneManager::Instance().GetPlayerTexture(tag) - 1 ),0,256,128));
			if (_i_player_data->GetStatusTag(tag) == ITEM_PLAYER_SPEEDUP)
			{
				SpriteBatch.Draw(*item_icon, banner_position + Vector3(30, 130, 0), RectWH(0, 0, 64, 64), 1.0f, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.7f);
				SpriteBatch.DrawString(player_font, _T("移動速度アップ！"), Vector2(banner_position.x, banner_position.y) + Vector2(75, 140),
					Color(255, 255, 255), Vector2(0.4, 0.4), Vector3(0, 0, 0), Vector3(0, 0, 0));
			}
			else if (_i_player_data->GetStatusTag(tag) == ITEM_ARM_SPEEDUP)
			{
				SpriteBatch.Draw(*item_icon, banner_position + Vector3(30, 130, 0), RectWH( 64, 0, 64, 64), 1.0f, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.7f);
				SpriteBatch.DrawString(player_font, _T("アームの速度アップ！"), Vector2(banner_position.x, banner_position.y) + Vector2(75, 140),
					Color(255, 255, 255), Vector2(0.4, 0.4), Vector3(0, 0, 0), Vector3(0, 0, 0));
			}
			else if (_i_player_data->GetStatusTag(tag) == ITEM_POWERDOWN)
			{
				SpriteBatch.Draw(*item_icon, banner_position + Vector3(30, 130, 0), RectWH(128, 0, 64, 64), 1.0f, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.7f);
				SpriteBatch.DrawString(player_font, _T("ステータスダウン"), Vector2(banner_position.x, banner_position.y) + Vector2(75, 140),
					Color(255, 255, 255), Vector2(0.4, 0.4), Vector3(0, 0, 0), Vector3(0, 0, 0));
			}
			else if (_i_player_data->GetStatusTag(tag) == ITEM_THUNDER)
			{
				SpriteBatch.Draw(*item_icon, banner_position + Vector3(30, 130, 0), RectWH(192, 0, 64, 64), 1.0f, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.7f);
				SpriteBatch.DrawString(player_font, _T("THUNDER"), Vector2(banner_position.x, banner_position.y) + Vector2(75, 140),
					Color(255, 255, 255), Vector2(0.4, 0.4), Vector3(0, 0, 0), Vector3(0, 0, 0));
			}
			break;
		}
	}
	int seconds = TimeManager::Instance().GetTime();

	//! 入手ポイントのアニメーション
	for (int i = 0; i < pointAnimation.size(); i++)
	{
		for (int s = 1; s < FIRST_RANK_POINT / 10;s++) {
			if (pointAnimation[i].point >= s * 100) {
				if ((pointAnimation[i].point / 1000) >= 1) {
					SpriteBatch.Draw(*score_font, pointAnimation[i].position + Vector3(10 * ((0.1 * s) + 0.3f), -25, 0),
						RectWH(((int)((pointAnimation[i].point / 1000)) * 64), 0, 64, 64), pointAnimation[i].alpha, Vector3(0, 0, 0),
						Vector3(0, 0, 0), (0.1 * s) + 0.3f);
				}
				SpriteBatch.Draw(*score_font, pointAnimation[i].position + Vector3(74 * ((0.1 * s) + 0.3f), -25, 0),
					RectWH((int)((pointAnimation[i].point % 1000) / 100) * 64, 0, 64, 64), pointAnimation[i].alpha, Vector3(0, 0, 0),
					Vector3(0, 0, 0), (0.1 * s) + 0.3f);
				SpriteBatch.Draw(*score_font, pointAnimation[i].position + Vector3(138 * ((0.1 * s) + 0.3f), -25, 0),
					RectWH((int)((pointAnimation[i].point % 1000) % 100 / 10) * 64, 0, 64, 64), pointAnimation[i].alpha, Vector3(0, 0, 0),
					Vector3(0, 0, 0), (0.1 * s) + 0.3f);
				SpriteBatch.Draw(*score_font, pointAnimation[i].position + Vector3(204 * ((0.1 * s) + 0.3f), -25, 0),
					RectWH((int)((pointAnimation[i].point % 1000) % 100 % 10) * 64, 0, 64, 64), pointAnimation[i].alpha, Vector3(0, 0, 0),
					Vector3(0, 0, 0), (0.1 * s) + 0.3f);
				break;
			}
		}
	}
	//バナースコアアニメーション
	SpriteBatch.Draw(*score_font, banner_position + Vector3((10 * 0.6) + 50, 10, -1), RectWH((int)(score / 1000) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), _font_size);
	SpriteBatch.Draw(*score_font, banner_position + Vector3((74 * 0.6) + 50, 10, -1), RectWH((int)((score % 1000) / 100) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), _font_size);
	SpriteBatch.Draw(*score_font, banner_position + Vector3((138 * 0.6) + 50, 10, -1), RectWH((int)((score % 1000) % 100 / 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), _font_size);
	SpriteBatch.Draw(*score_font, banner_position + Vector3((204 * 0.6) + 50, 10, -1), RectWH((int)((score % 1000) % 100 % 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), _font_size);


	//! 一位のとき
	if (_i_player_data->GetRankNum(tag) + 1 == 1)
	{
		SpriteBatch.Draw(*joy_icon, banner_position + Vector3( 90, -123, -1), RectWH(SceneManager::Instance().GetPlayerTexture(tag) * 128 - 128, 0, 128, 128), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 1.f);
	}
	else
	{
		SpriteBatch.Draw(*joy_icon, banner_position + Vector3( 80, -125*1.1f, -1), RectWH(SceneManager::Instance().GetPlayerTexture(tag) * 128 - 128, 128, 128, 128), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 1.1f);
	}
	SpriteBatch.Draw(*ranking, player_pos + Vector3(-50 * 0.7, (-128 - 40) * 0.7, 0), RectWH((_i_player_data->GetRankNum(tag)) * 128, 0, 128, 128), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.7f);
	//! 開始十秒後に順位表示
	if (seconds < 10) {
		
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
	if (pointAnimation.size() == 0)
	{
		return;
	}
	//! 入手ポイントの移動
	for (int i = 0; i < pointAnimation.size(); ++i)
	{
		Vector3 bezier  = Vector3_Bezier(player_num, corner[0], corner[0], player_num + Vector3( -80, 0, 0), pointAnimation[i].theta);
		Vector3 bezier2 = Vector3_Bezier(player_num, corner[1], corner[1], player_num + Vector3( -80, 0, 0), pointAnimation[i].theta);
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

		////! バナーの座標に入手したポイントがたどり着いたとき 1p & 3p
		//if (player_index == 0 || player_index == 2) {
		//	if (pointAnimation[i].position.x <= banner_position.x + 100) {
		//		add_point += pointAnimation[i].point;
		//		_font_size = 0.6 + ((float)(add_point - score) / (float)1000);
		//		delta_point = (add_point - score) / GameTimer.GetFPS() * 4;
		//		pointAnimation.erase(pointAnimation.begin() + i);
		//	}
		//}

		////! バナーの座標に入手したポイントがたどり着いたとき 2p & 4p
		//if (player_index == 1 || player_index == 3) {
		//	if (pointAnimation[i].position.x >= banner_position.x + 100) {
		//		add_point += pointAnimation[i].point;
		//		_font_size = 0.6 + ((float)(add_point - score) / (float)1000);
		//		delta_point = (add_point - score) / GameTimer.GetFPS() * 4;
		//		pointAnimation.erase(pointAnimation.begin() + i);
		//	}
		//}

		//! playerの座標に入手したポイントがたどり着いたとき 1p & 2p
		if (player_index == 0 || player_index == 1) {
			if (pointAnimation[i].position.y >= player_num.y + 3) {
				add_point += pointAnimation[i].point;
				_font_size = 0.6 + ((float)(add_point - score) / (float)1000);
				delta_point = (add_point - score) / GameTimer.GetFPS() * 4;
				pointAnimation.erase(pointAnimation.begin() + i);
			}
		}

		//!  playerの座標に入手したポイントがたどり着いたとき 3p & 4p
		if (player_index == 2 || player_index == 3) {
			if (pointAnimation[i].position.y <= player_num.y - 3) {
				add_point += pointAnimation[i].point;
				_font_size = 0.6 + ((float)(add_point - score) / (float)1000);
				delta_point = (add_point - score) / GameTimer.GetFPS() * 4;
				pointAnimation.erase(pointAnimation.begin() + i);
			}
		}
	}
}

