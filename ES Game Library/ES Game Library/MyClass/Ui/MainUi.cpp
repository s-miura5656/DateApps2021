#include "MainUi.h"
#include "../Data/WordsTable.h"
#include "../Managers/TimeManager/Time.h"
#include "../Players/PlayerBase.h"
#include "../Managers/ResouceManager/ResouceManager.h"
#include "../Managers/SceneManager/SceneManager.h"
#include <codecvt>


MainUi::MainUi()
{
	_i_player_data = new IPrayerData;
	_i_arm_data = new IArmData;
}

MainUi::~MainUi()
{
	delete _i_arm_data;
	delete _i_player_data;
}

bool MainUi::Initialize()
{
	//!file
	time_limit_font = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 50);
	back_count = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 95);
	front_count = ResouceManager::Instance().LordFontFile(_T("チェックアンドU-Foフォント"), 90);

	time_banner = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/time_2.png"));
	number_sprite = ResouceManager::Instance().LordSpriteFile(_T("NumberSprite/namber.png"));
	start_end         = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/Start_finish.png"));

	time_banner_pos = Vector3(640 - 125, 10, 1);
	minutes_pos = Vector3(530, 20, 0);
	tens_place_pos = Vector3(630, 20, 0);
	ones_place_pos = Vector3(690, 20, 0);
	colon_pos = Vector3(580, 20, 0);

	/*minutes_pos_v2_w    = Vector2(543, 23) + Vector2(0,100);
	tens_place_pos_v2_w = Vector2(633, 23) + Vector2(0, 100);
	ones_place_pos_v2_w = Vector2(683, 23) + Vector2(0, 100);

	minutes_pos_v2_b    = Vector2(540, 20) + Vector2(0, 100);
	tens_place_pos_v2_b = Vector2(630, 20) + Vector2(0, 100);
	ones_place_pos_v2_b = Vector2(680, 20) + Vector2(0, 100);*/

	Countdown_pos = Vector3(605, 345, -2000);
	cout_size = 1.0f;
	rt = 0;
	s_or_e = false;
	old_time = 0;
	end_a = 1.0f;
	font_size_e = 1.0f;

	start_size = 1.0f;
	start_a = 1.0f;
	finsh_size = 1.0f;
	finsh_a = 1.0f;
	a_and_e = false;

	score_pos[0] = Vector2(100, 40);
	score_pos[1] = Vector2(320, 40);
	score_pos[2] = Vector2(800, 40);
	score_pos[3] = Vector2(1020, 40);

	speed_ui_pos[0] = Vector2(10, 60);
	speed_ui_pos[1] = Vector2(1025, 60);
	speed_ui_pos[2] = Vector2(10, 680);
	speed_ui_pos[3] = Vector2(1025, 680);

	black = Color(0.f, 0.f, 0.f);
	White = Color(1.f, 1.f, 1.f);

	time_size_pp = false;
	time_limit_decreasing = false;
	font_size = 0.8f;
	time_size_up = 0.0;
	time_size_down = 0.0;
	time_size_flag = false;

	for (int i = 0; i < _countof(number); i++)
	{
		number[i] = RectWH(i * 64, 0, 64, 64);
	}

	for (int i = 0; i < _countof(start_end_rect); i++) 
	{
		start_end_rect[i] = RectWH(i * 384, 0, 384, 64);
	}

	Danger = Color(255, 255, 255);
	r = 255;
	g = 255;
	b = 255;
	Blinking = false;

	// Player1
	player_ui.push_back(new PlayerUi(0));
	player_ui[0]->Initialize(Vector3(10, 200, 1), RectWH(256 * (SceneManager::Instance().GetPlayerTexture("Player_1") - 1),0,256,64));

	// Player2
	player_ui.push_back(new PlayerUi(1));
	player_ui[1]->Initialize(Vector3(1280 - 250, 200, 1), RectWH(256 * (SceneManager::Instance().GetPlayerTexture("Player_2") - 1), 0, 256, 64));

	// Player3
	player_ui.push_back(new PlayerUi(2));
	player_ui[2]->Initialize(Vector3(10, 500, 1), RectWH(256 * (SceneManager::Instance().GetPlayerTexture("Player_3") - 1), 0, 256, 64));

	// Player4
	player_ui.push_back(new PlayerUi(3));
	player_ui[3]->Initialize(Vector3(1280 - 250, 500, 1), RectWH(256 * (SceneManager::Instance().GetPlayerTexture("Player_4") - 1), 0, 256, 64));
	
	return true;
}

int MainUi::Update()
{
	for (auto&& pui : player_ui)
		pui->Update();

	float time_limit_f = TimeManager::Instance().GetTimeLeft();
	int time_limit     = TimeManager::Instance().GetTimeLeft();
	float start_time   = TimeManager::Instance().GetStartTime();
	int Countdown      = TimeManager::Instance().Countdown();

	//! S T A R T !!とF I N S H !!　の切り替え
	if (Countdown < 0) {
		s_or_e = true;
	}

	if (Countdown == 0) {
		a_and_e = true;
	}
	
	//! S T A R T　のとき
	if (a_and_e == true) {
		start_size += 0.02f;
	}
	if (start_size >=1.2) {
		start_a -= 0.02f;
	}
	if (start_a <= 0) {
		start_a = 1.0f;
		start_a = 1.0f;
		a_and_e = false;
	}

	//! F I N S H のとき
	if (TimeManager::Instance().GetTransitionTimer() > 0 && finsh_size <= 1.2f) {
		finsh_size += 0.02f;
	}
	
	//! カウントダウンサイズのリセット
	if (start_time == 180 || start_time == 120 || start_time == 60 || start_time == 0) {
		cout_size = 1.0f;
		rt = 0;
	}

	//! カウントダウンの回転と縮小
	if (start_time <= 30.0f && Countdown == 1) {
		rt += 11;
		cout_size -= 0.04;
	}
	else if (start_time <= 90.0f && Countdown == 2) {
		rt += 11;
		cout_size -= 0.04;
	}
	else if (start_time <= 150.0f && Countdown == 3) {
		rt += 11;
		cout_size -= 0.04;
	}
	
	//! 終了カウントダウンリセット
	if (old_time != time_limit) {
		font_size_e = 1.0;
		end_a = 1.0f;
	}
	//! 終了カウントダウンの拡大
	for (int i = 1; i < 4; i++)
	{
		if (time_limit == i) {
			font_size_e += 0.02;
			end_a -= 0.01;
			old_time = i;
		}
	}
	
	//! 60秒になったらタイマーの拡大
	if (time_limit == 60) {
		time_limit_decreasing = true;
	}
	if (time_limit_decreasing == true && font_size <= 1.5) {
		font_size += time_size_up;
	}
	if (font_size >= 1.5) {
		time_limit_decreasing = false;
	}
	if (font_size >= 0.8 && time_limit_decreasing == false) {
		font_size -= time_size_down;
	}

	if (time_limit <= 30 && time_limit > 0)
	{
		MainUi::ColorBlinking();
		MainUi::TimeSizeFluctuation();

		//! 十秒ごとに拡大縮小のサイズ変更 
		if (time_limit % 10 == 0) {
			if (!time_size_pp) {
				time_size_up += 0.02f;
				time_size_down += 0.01f;
				time_size_pp = true;
			}
		}
		else {
			time_size_pp = false;
		}
	}
	
	return 0;
}

void MainUi::Draw2D()
{
	for (auto& pui : player_ui)
		pui->Draw2D();

	float time_limit_f = TimeManager::Instance().GetTimeLeft();
	int time_limit = TimeManager::Instance().GetTimeLeft();
	int minutes   = TimeManager::Instance().GetTimeMinutes();
	//int seconds   = TimeManager::Instance().GetTimeSeconds();
	int ones      = TimeManager::Instance().GetTimeOnesPlace();
	int tens      = TimeManager::Instance().GetTimeTensPlace();
	int Countdown = TimeManager::Instance().Countdown();
	float Start   = TimeManager::Instance().GetStartTime();
	
	SpriteBatch.Draw(*number_sprite, minutes_pos, number[minutes], (DWORD)Danger, Vector3(0, 0, 0), Vector3(96, 32, 0), font_size);
	SpriteBatch.Draw(*number_sprite, colon_pos, number[10]       , (DWORD)Danger, Vector3(0, 0, 0), Vector3(64, 32, 0), font_size);
	SpriteBatch.Draw(*number_sprite, tens_place_pos, number[tens], (DWORD)Danger, Vector3(0, 0, 0), Vector3(32, 32, 0), font_size);
	SpriteBatch.Draw(*number_sprite, ones_place_pos, number[ones], (DWORD)Danger, Vector3(0, 0, 0), Vector3(-32, 32, 0), font_size);

	/*SpriteBatch.DrawString(time_limit_font, minutes_pos_v2_b, black, Vector2(1.15f, 1.15f), Vector3(0, 0, 0), Vector3(0, 0, 0), _T("%d"), minutes);
	SpriteBatch.DrawString(time_limit_font, tens_place_pos_v2_b, black, Vector2(1.15f, 1.15f), Vector3(0, 0, 0), Vector3(0, 0, 0), _T("%d"), tens);
	SpriteBatch.DrawString(time_limit_font, ones_place_pos_v2_b, black, Vector2(1.15f, 1.15f), Vector3(0, 0, 0), Vector3(0, 0, 0), _T("%d"), ones);

	SpriteBatch.DrawString(time_limit_font, minutes_pos_v2_w, White, Vector2(1.0f, 1.0f), Vector3(0, 0, 0), Vector3(0, 0, 0), _T("%d"), minutes);
	SpriteBatch.DrawString(time_limit_font, tens_place_pos_v2_w, White, Vector2(1.0f, 1.0f), Vector3(0, 0, 0), Vector3(0, 0, 0), _T("%d"), tens);
	SpriteBatch.DrawString(time_limit_font, ones_place_pos_v2_w, White, Vector2(1.0f, 1.0f), Vector3(0, 0, 0), Vector3(0, 0, 0), _T("%d"), ones);*/

	SpriteBatch.Draw(*time_banner, time_banner_pos);

	//! カウントダウン描写
	if (Start > 0)
	{
		SpriteBatch.Draw(*number_sprite, Countdown_pos, number[Countdown], (DWORD)White, Vector3(0, 0, rt), Vector3( 32, 32, 0), cout_size);
	}

	//! スタート描写
	if (Countdown == 0) 
	{
		SpriteBatch.Draw(*start_end, Vector3(450, 340, 0), start_end_rect[s_or_e], start_a, Vector3(0, 0, 0), Vector3(192, 32, 0), start_size);
	}
	
	//! 終了
	if (TimeManager::Instance().GetTransitionTimer() > 0)
	{
		SpriteBatch.Draw(*start_end, Vector3(450, 340, 0), start_end_rect[s_or_e], finsh_a, Vector3(0, 0, 0), Vector3(192, 32, 0), finsh_size);
	}
	else if ((minutes == 0 && tens == 0) && ones <= 3)
	{
		SpriteBatch.Draw(*number_sprite, Countdown_pos, number[ones], end_a, Vector3(0, 0, 0), Vector3(32, 32, 0), font_size_e);
	}


}

void MainUi::ColorBlinking()
{
	Danger = Color(r, g, b);
	//! 赤点滅
	if (g >= 0 && b >= 0 && Blinking == false) {
		g -= 5;
		b -= 5;
		if (g < 0 || b < 0)
		{
			g = 0;
			b = 0;
			Blinking = true;
		}
	}
	//! 白点滅
	else if (Blinking == true) {
		g += 5;
		b += 5;
		if (g > 255 || b > 255) {
			g = 255;
			b = 255;
			Blinking = false;
		}
	}
}

void MainUi::TimeSizeFluctuation()
{
	//! 拡大
	if (time_size_flag == false && font_size <= 1.2) {
		font_size += time_size_up;
		if (font_size >= 1.2) {
			font_size = 1.2f;
			time_size_flag = true;
		}
	}
	//! 縮小
	else if (time_size_flag == true) {
		font_size -= time_size_down;
		if (font_size <= 0.8) {
			font_size = 0.8f;
			time_size_flag = false;
		}
	}
}




