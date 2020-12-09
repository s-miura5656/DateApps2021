#include "MainUi.h"
#include "../Data/IData.h"
#include "../Data/WordsTable.h"
#include "../Managers/TimeManager/Time.h"
#include "../Players/PlayerBase.h"

MainUi::MainUi()
{
	i_player_data = new IPrayerData;
	
}

MainUi::~MainUi()
{

}


bool MainUi::Initialize()
{
	time_limit_font = GraphicsDevice.CreateSpriteFont(_T("チェックアンドU-Foフォント"), 50);
	player_date     = GraphicsDevice.CreateSpriteFont(_T("MS ゴシック"), 20);
	red_banner      = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/red2.png"));
	blue_banner     = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/blue2.png"));
	green_banner    = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/green2.png"));
	yellow_banner   = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/yellow2.png"));
	time_banner     = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/time_2.png"));
	score_num       = GraphicsDevice.CreateSpriteFromFile(_T("NumberSprite/number_3.png"));

	banner_pos[0] = Vector3(80  , 30, 1);
	banner_pos[1] = Vector3(300 , 30, 1);
	banner_pos[2] = Vector3(800 , 30, 1);
	banner_pos[3] = Vector3(1020, 30, 1);

	score_pos[0] = Vector2( 100,   40);
	score_pos[1] = Vector2( 320,   40);
	score_pos[2] = Vector2( 820,   40);
	score_pos[3] = Vector2(1040,   40);
	
	

	speed_ui_pos[0] = Vector2(  10,  60);
	speed_ui_pos[1] = Vector2(1025,  60);
	speed_ui_pos[2] = Vector2(  10, 680);
	speed_ui_pos[3] = Vector2(1025, 680);

	color[0] = Color(255,   0, 0  );
	color[1] = Color(0  ,   0, 255);
	color[2] = Color(0  , 255, 0  );
	color[3] = Color(255, 255,  0 );

	InputDevice.CreateKeyboard();

	return true;
}

void MainUi::Draw2D()
{
	

	int minutes = TimeManager::Instance().GetTimeMinutes();
	int seconds = TimeManager::Instance().GetTimeSeconds();

	
	/*SpriteBatch.DrawString(time_limit_font, Vector2(570, 20), Color(1.f, 1.f, 1.f), _T("%d"), TimeManager::Instance().TimeLeft());
	SpriteBatch.DrawString(time_limit_font, Vector2(590, 20), Color(1.f, 1.f, 1.f), _T("%d"), TimeManager::Instance().TimeMid());
	SpriteBatch.DrawString(time_limit_font, Vector2(610, 20), Color(1.f, 1.f, 1.f), _T("%d"), TimeManager::Instance().TimeRight());*/
	/*SpriteBatch.DrawString(time_limit_font, Vector2(570, 20), Color(1.f, 1.f, 1.f), _T("%1.0f"), TimeManager::Instance().GetTimeLeft());*/
	if (minutes == 3) {
		SpriteBatch.DrawString(time_limit_font, Vector2(540, 20), Color(1.f, 1.f, 1.f), _T("0%d:0%d"), minutes, seconds);
	}
	else if ( ((minutes == 2) && (seconds < 20 && seconds >= 10)) || (minutes == 0) && (seconds < 20 && seconds >= 10) ) {
		SpriteBatch.DrawString(time_limit_font, Vector2(540, 20), Color(1.f, 1.f, 1.f), _T("0%d: %d"), minutes, seconds);
	}
	else if ( (minutes == 2 && seconds < 10) || (minutes == 0 && seconds < 10) ) {
		SpriteBatch.DrawString(time_limit_font, Vector2(540, 20), Color(1.f, 1.f, 1.f), _T("0%d:0%d"), minutes, seconds);
	}
	else if ((minutes == 1) && (seconds < 20 && seconds >= 10)) {
		SpriteBatch.DrawString(time_limit_font, Vector2(540, 20), Color(1.f, 1.f, 1.f), _T("0%d : %d"), minutes, seconds);
	}
	else if (minutes == 1 && seconds < 10) {
		SpriteBatch.DrawString(time_limit_font, Vector2(540, 20), Color(1.f, 1.f, 1.f), _T("0%d :0%d"), minutes, seconds);
	}
	else if (minutes == 1) {
		SpriteBatch.DrawString(time_limit_font, Vector2(540, 20), Color(1.f, 1.f, 1.f), _T("0%d :%d"), minutes, seconds);
	} 
	else 
	{
		SpriteBatch.DrawString(time_limit_font, Vector2(540, 20), Color(1.f, 1.f, 1.f), _T("0%d:%d"), minutes, seconds);
	}

	
	SpriteBatch.Draw(*time_banner, Vector3(640-125, 5,1));
	PlayerBanner();
}


void MainUi::PlayerBanner()
{
	auto param_list = i_player_data->GetAllParametor();
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string& tag = PLAYER_TAG + std::to_string(i + 1);
	
		
		//int score = param_list[tag].ranking_point;
		int score = iplayer_data->GetRankingPoint(tag);

		SpriteBatch.DrawString(player_date, score_pos[i], color[i], _T("%dp_Point : %d"), i+1, iplayer_data->GetRankingPoint(tag));
		SpriteBatch.Draw(*red_banner, banner_pos[0]);
		SpriteBatch.Draw(*blue_banner, banner_pos[1]);
		SpriteBatch.Draw(*green_banner, banner_pos[2]);
		SpriteBatch.Draw(*yellow_banner, banner_pos[3]);


		//スコアアニメーション
		if (score > 999)
		{
			SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3(100, 0, -1), RectWH((int)(score / 1000) * 64  , 0, 64, 64));
			SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3(200, 0, -1), RectWH((int)((score % 1000) / 100) * 64, 0, 64, 64));
			SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3(300, 0, -1), RectWH((int)((score % 1000) % 100 / 10) * 64, 0, 64, 64));
			SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3(400, 0, -1), RectWH((int)((score % 1000) % 100 % 10) * 64, 0, 64, 64));
		}
		else if (score > 99)
		{
			SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3(100, 0, -1), RectWH((int)(score / 100) * 64, 0, 100, 64));
			SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3(200, 0, -1), RectWH((int)((score % 100) / 10) * 64, 0, 64, 64));
			SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3(300, 0, -1), RectWH((int)((score % 100) % 10) * 64, 0, 64, 64));
		}
		else if (score > 9)
		{
			SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3(100, 0, -1), RectWH((int)(score / 10) * 64, 0, 64, 64));
			SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3(200, 0, -1), RectWH((int)(score % 10) * 64, 0, 64, 64));
		}
		else
		{
			SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3(100, 0, -1), RectWH((int)(score) * 64, 0, 64, 64));
		}

	}
}

