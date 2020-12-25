#include "MainUi.h"
#include "../Data/IData.h"
#include "../Data/WordsTable.h"
#include "../Managers/TimeManager/Time.h"
#include "../Players/PlayerBase.h"
#include "../Managers/ResouceManager/ResouceManager.h"
#include <codecvt>


MainUi::MainUi()
{
	_i_player_data.reset(new IPrayerData);
	_i_arm_data.reset(new IArmData);
}

MainUi::~MainUi()
{
	_i_arm_data.reset();
	_i_player_data.reset();
}

bool MainUi::Initialize()
{

	//!file
	time_limit_font   = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 50);
	back_count        = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 95);
	front_count       = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 90);

	time_banner       = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/time_2.png"));
	number_sprite     = ResouceManager::Instance().LordSpriteFile(_T("NumberSprite/number_3.png"));

	score_pos[0] = Vector2( 100,   40);
	score_pos[1] = Vector2( 320,   40);
	score_pos[2] = Vector2( 800,   40);
	score_pos[3] = Vector2(1020,   40);
	
	speed_ui_pos[0] = Vector2(  10,  60);
	speed_ui_pos[1] = Vector2(1025,  60);
	speed_ui_pos[2] = Vector2(  10, 680);
	speed_ui_pos[3] = Vector2(1025, 680);

	color[0] = Color(255,   0,   0);
	color[1] = Color(  0,   0, 255);
	color[2] = Color(255, 255,   0);
	color[3] = Color(  0, 255,   0);

	for (int i = 0; i < 10; i++)
	{
		number[i] = RectWH(i * 64, 0, 64, 64);
	}
	
	// Player1
	player_ui.push_back(PlayerUi(0));
	player_ui[0].Initialize(_T("BannerFrameSprite/red_banner.png"), Vector3(80, 30, 1));

	// Player2
	player_ui.push_back(PlayerUi(1));
	player_ui[1].Initialize(_T("BannerFrameSprite/blue_banner.png"), Vector3(300, 30, 1));

	// Player3
	player_ui.push_back(PlayerUi(2));
	player_ui[2].Initialize(_T("BannerFrameSprite/green_banner.png"), Vector3(780, 30, 1));

	// Player4
	player_ui.push_back(PlayerUi(3));
	player_ui[3].Initialize(_T("BannerFrameSprite/yellow_banner.png"), Vector3(1000, 30, 1));

	
	return true;
}

int MainUi::Update()
{
	for (auto& pui : player_ui)
		pui.Update();

	return 0;
}

void MainUi::Draw2D()
{
	for (auto& pui : player_ui)
		pui.Draw2D();

	int minutes   = TimeManager::Instance().GetTimeMinutes();
	int seconds   = TimeManager::Instance().GetTimeSeconds();
	int ones      = TimeManager::Instance().GetTimeOnesPlace();
	int tens      = TimeManager::Instance().GetTimeTensPlace();
	int Countdown = TimeManager::Instance().Countdown();
	float Start   = TimeManager::Instance().GetStartTime();
	
	/*SpriteBatch.Draw(*number_sprite, Vector3(540, 20, 0), number[minutes]);*/
	/*SpriteBatch.Draw(*number_sprite, Vector3(540, 20, 0), number[ones]);
	SpriteBatch.Draw(*number_sprite, Vector3(540, 20, 0), number[tens]);*/
	SpriteBatch.DrawString(time_limit_font, Vector2(540, 20), Color(1.f, 1.f, 1.f), _T("%02d:%02d"), minutes, seconds);

	SpriteBatch.Draw(*time_banner, Vector3(640 - 125, 5, 1));

	//! カウントダウン描写（影）
	if (Start > 0)
	{
		SpriteBatch.DrawString(back_count , Vector2(600, 340), Color(0.f, 0.f, 0.f), _T("%d"), Countdown);
	}

	//! カウントダウン描写（手前の文字）
	if (Start > 0)
	{
		SpriteBatch.DrawString(front_count, Vector2(605, 345), Color(1.f, 1.f, 1.f), _T("%d"), Countdown);
	}

	//! スタート描写（影）
	if (Countdown == 0) 
	{
		SpriteBatch.DrawString(back_count , Vector2(487, 340), Color(0.f, 0.f, 0.f), _T("S T A R T !!"));
	}

	//! スタート描写（手前の文字）
	if (Countdown == 0) 
	{
		SpriteBatch.DrawString(front_count, Vector2(500, 340), Color(1.f, 1.f, 1.f), _T("S T A R T !!"));
	}
}




