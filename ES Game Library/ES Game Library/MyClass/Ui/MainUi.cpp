#include "MainUi.h"
#include "../Data/IData.h"
#include "../Data/WordsTable.h"
#include "../Managers/TimeManager/Time.h"
#include "../Players/PlayerBase.h"
#include <codecvt>

MainUi::MainUi()
{
	i_player_data = new IPrayerData;
	i_arm_data    = new IArmData;
	
}

MainUi::~MainUi()
{

}


bool MainUi::Initialize()
{
	time_limit_font = GraphicsDevice.CreateSpriteFont(_T("チェックアンドU-Foフォント"), 50);
	red_banner      = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/red_banner.png"));
	blue_banner     = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/blue_banner.png"));
	green_banner    = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/green_banner.png"));
	yellow_banner   = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/yellow_banner.png"));
	time_banner     = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/time_2.png"));
	score_num       = GraphicsDevice.CreateSpriteFromFile(_T("NumberSprite/namber.png"));
	kuro            = GraphicsDevice.CreateSpriteFont(_T("チェックアンドU-Foフォント"), 95);
	siro            = GraphicsDevice.CreateSpriteFont(_T("チェックアンドU-Foフォント"), 90);

	test = GraphicsDevice.CreateSpriteFromFile(_T("HpSprite/ゲージベース2.png"));
	flag = 0;


	banner_pos[0] = Vector3(80  , 30, 1);
	banner_pos[1] = Vector3(300 , 30, 1);
	banner_pos[2] = Vector3(780 , 30, 1);
	banner_pos[3] = Vector3(1000, 30, 1);

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
	
	InputDevice.CreateKeyboard();

	return true;
}

void MainUi::Draw2D()
{
	

	int minutes   = TimeManager::Instance().GetTimeMinutes();
	int seconds   = TimeManager::Instance().GetTimeSeconds();
	int Countdown = TimeManager::Instance().Countdown();
	float Start   = TimeManager::Instance().GetstartTime();
	
	tstring a = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes("");
	SpriteBatch.DrawString(time_limit_font, Vector2(540, 20), Color(1.f, 1.f, 1.f), _T("%02d:%02d"), minutes, seconds);

	SpriteBatch.Draw(*time_banner, Vector3(640-125, 5,1));
	PlayerBanner();
	PointAnimation();
	if (Start > 0) {
		SpriteBatch.DrawString(kuro, Vector2(600, 340), Color(0.f, 0.f, 0.f), _T("%d"), Countdown);
	}
	if (Start > 0) {
		SpriteBatch.DrawString(siro, Vector2(605, 345), Color(1.f, 1.f, 1.f), _T("%d"), Countdown);
	}
	if (Countdown == 0) {
		SpriteBatch.DrawString(kuro, Vector2(387, 340), Color(0.f, 0.f, 0.f), _T("S T A R T !!"));
	}
	if (Countdown == 0) {
		SpriteBatch.DrawString(siro, Vector2(400, 340), Color(1.f, 1.f, 1.f), _T("S T A R T !!"));
	}
}


void MainUi::PlayerBanner()
{
	auto param_list = i_player_data->GetAllParametor();
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string& tag = PLAYER_TAG + std::to_string(i + 1);

		int score = iplayer_data->GetRankingPoint(tag);

		
		SpriteBatch.Draw(*red_banner, banner_pos[0]);
		SpriteBatch.Draw(*blue_banner, banner_pos[1]);
		SpriteBatch.Draw(*yellow_banner, banner_pos[2]);
		SpriteBatch.Draw(*green_banner, banner_pos[3]);
		

		//スコアアニメーション
		SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3( (10 * 0.3) + 90,  10, -1), RectWH((int)(score / 1000) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0),Vector3(0,0,0),0.3f);
		SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3( (74 * 0.3) + 90,  10, -1), RectWH((int)((score % 1000) / 100) * 64, 0, 64, 64),(DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);
		SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3( (138 * 0.3) + 90, 10, -1), RectWH((int)((score % 1000) % 100 / 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);
		SpriteBatch.Draw(*score_num, banner_pos[i] + Vector3( (204 * 0.3) + 90, 10, -1), RectWH((int)((score % 1000) % 100 % 10) * 64, 0, 64, 64), (DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f);
	}
}

void MainUi::PointAnimation()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string& arm_tag = ARM_TAG + std::to_string(i + 1);
		auto pos = i_arm_data->GetHitPosition(arm_tag);
		if (pos != Vector3_Zero) {
//			SpriteBatch.Draw(*test, pos);
		}
	}

}

