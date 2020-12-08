#include "MainUi.h"
#include "../Data/IData.h"
#include "../Data/WordsTable.h"
#include "../Managers/TimeManager/Time.h"
#include "../Players/PlayerBase.h"

MainUi::MainUi()
{
	iplayer_data = new IPrayerData;
}

MainUi::~MainUi()
{

}


bool MainUi::Initialize()
{
	time_limit_font = GraphicsDevice.CreateSpriteFont(_T("チェックアンドU-Foフォント"), 50);
	player_date     = GraphicsDevice.CreateSpriteFont(_T("SketchFlow Print"), 20);
	red_banner      = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/red.png"));
	blue_banner     = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/blue.png"));
	green_banner    = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/green.png"));
	yellow_banner   = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/yellow.png"));
	time_banner     = GraphicsDevice.CreateSpriteFromFile(_T("BannerFrameSprite/time.png"));

	powor_ui_pos[0] = Vector2(  10,   50);
	powor_ui_pos[1] = Vector2(950 ,   50);
	powor_ui_pos[2] = Vector2(  10,  570);
	powor_ui_pos[3] = Vector2(950 ,  570);
	
	hp_ui_pos[0] = Vector3(  10,  30,0);
	hp_ui_pos[1] = Vector3(1050,  30,0);
	hp_ui_pos[2] = Vector3(  10, 650,0);
	hp_ui_pos[3] = Vector3(1050, 650,0);

	/*speed_ui_pos[0] = Vector2(  10,  60);
	speed_ui_pos[1] = Vector2(1025,  60);
	speed_ui_pos[2] = Vector2(  10, 680);
	speed_ui_pos[3] = Vector2(1025, 680);*/

	color[0] = Color(255, 0  , 0);
	color[1] = Color(0  , 255, 0);
	color[2] = Color(0  ,  0 ,255);
	color[3] = Color(255, 255,  0);

	InputDevice.CreateKeyboard();

	return true;
}

void MainUi::Draw2D()
{
	
	int minutes = TimeManager::Instance().GetTimeMinutes();
	int seconds = TimeManager::Instance().GetTimeSeconds();
	
	if (seconds < 10)
	{
		SpriteBatch.DrawString(time_limit_font, Vector2(600, 20), Color(1.f, 1.f, 1.f), _T("%d:0%d"), minutes, seconds);
	}
	else if (seconds < 20 && seconds >= 10)
	{
		SpriteBatch.DrawString(time_limit_font, Vector2(600, 20), Color(1.f, 1.f, 1.f), _T("%d: %d"), minutes, seconds);
	}
	else 
	{
		SpriteBatch.DrawString(time_limit_font, Vector2(600, 20), Color(1.f, 1.f, 1.f), _T("%d:%d"), minutes, seconds);
	}
	SpriteBatch.Draw(*time_banner, Vector3(550, 5,1));
	PlayerBanner();
}


void MainUi::PlayerBanner()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string& tag = PLAYER_TAG + std::to_string(i + 1);

		const auto banner = powor_ui_pos[i];//スコアを書き込む

		SpriteBatch.Draw(*red_banner, hp_ui_pos[0]);
		SpriteBatch.Draw(*blue_banner, hp_ui_pos[1]);
		SpriteBatch.Draw(*green_banner, hp_ui_pos[2]);
		SpriteBatch.Draw(*yellow_banner, hp_ui_pos[3]);


	}
}



//攻撃、hp、スピード
