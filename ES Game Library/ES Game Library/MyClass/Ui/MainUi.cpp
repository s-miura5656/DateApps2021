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

	time_banner_pos = Vector3(640 - 125, 5, 1);
	minutes_pos     = Vector3(540, 20, 0);
	tens_place_pos  = Vector3(630, 20, 0);
	ones_place_pos  = Vector3(680, 20, 0);

	Countdown_pos   = Vector3(605, 345, 0);

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

	black    = Color(0.f, 0.f, 0.f);
	White    = Color(1.f, 1.f, 1.f);

	for (int i = 0; i < _countof(number); i++)
	{
		number[i] = RectWH(i * 64, 0, 64, 64);
	}
	
	// Player1
	player_ui.push_back(PlayerUi(0));
	player_ui[0].Initialize(_T("BannerFrameSprite/red_banner.png"), Vector3(10, 50, 1));

	// Player2
	player_ui.push_back(PlayerUi(1));
	player_ui[1].Initialize(_T("BannerFrameSprite/blue_banner.png"), Vector3(1280 - 300, 50, 1));

	// Player3
	player_ui.push_back(PlayerUi(2));
	player_ui[2].Initialize(_T("BannerFrameSprite/green_banner.png"), Vector3(10, 300, 1));

	// Player4
	player_ui.push_back(PlayerUi(3));
	player_ui[3].Initialize(_T("BannerFrameSprite/yellow_banner.png"), Vector3(1280 - 300, 300, 1));
	
	return true;
}

int MainUi::Update()
{
	for (auto&& pui : player_ui)
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
	
	SpriteBatch.Draw(*number_sprite, minutes_pos, number[minutes], (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.8f);
	SpriteBatch.Draw(*number_sprite, tens_place_pos, number[tens], (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.8f);
	SpriteBatch.Draw(*number_sprite, ones_place_pos, number[ones], (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.8f);

	SpriteBatch.DrawString(back_count, Vector2(595, 20), black, _T(":"));
	SpriteBatch.DrawString(time_limit_font, Vector2(595, 20), White, _T(":"));

	SpriteBatch.Draw(*time_banner, time_banner_pos);

	//! カウントダウン描写
	if (Start > 0)
	{
		SpriteBatch.Draw(*number_sprite, Countdown_pos, number[Countdown]);
	}

	//! スタート描写（影）
	if (Countdown == 0) 
	{
		SpriteBatch.DrawString(back_count , Vector2(487, 340), black, _T("S T A R T !!"));
	}

	//! スタート描写（手前の文字）
	if (Countdown == 0) 
	{
		SpriteBatch.DrawString(front_count, Vector2(500, 340), White, _T("S T A R T !!"));
	}

	//! タイムリミット（三秒前）
	if ((minutes == 0 && tens == 0) && ones <= 3)
	{
		SpriteBatch.Draw(*number_sprite, Countdown_pos, number[ones]);
	}

}




