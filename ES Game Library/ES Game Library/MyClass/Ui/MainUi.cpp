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
	time_limit_font = GraphicsDevice.CreateSpriteFont(_T("SketchFlow Print"), 50);
	player_date = GraphicsDevice.CreateSpriteFont(_T("SketchFlow Print"), 30);
	hp = GraphicsDevice.CreateSpriteFromFile(_T("ゲージベース2.png"));

	hp_x =1000.0f;
	hp_y = 25.0f;

	powor_ui_pos[0] = Vector2(  10,   0);
	powor_ui_pos[1] = Vector2(1025,   0);
	powor_ui_pos[2] = Vector2(  10, 620);
	powor_ui_pos[3] = Vector2(1025, 620);
	
	/*hp_ui_pos[0] = Vector2(  10,  30);
	hp_ui_pos[1] = Vector2(1025,  30);
	hp_ui_pos[2] = Vector2(  10, 650);
	hp_ui_pos[3] = Vector2(1025, 650);

	speed_ui_pos[0] = Vector2(  10,  60);
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
	SpriteBatch.DrawString(time_limit_font, Vector2(530, 0), Color(1.f, 1.f, 1.f), _T("TIME : %d"), int(TimeManager::Instance().GetTimeLeft()));
	DebugDraw();
}

void MainUi::DebugDraw()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string& tag = PLAYER_TAG + std::to_string(i + 1);
		
		const auto power_pos = powor_ui_pos[i];
		const auto text_color = color[i];

		SpriteBatch.DrawString(player_date, power_pos, text_color, _T("PLAYER_ATK : %d"), iplayer_data->GetAttackPowor(tag));
		SpriteBatch.DrawString(player_date, power_pos + Vector2(0, 30), text_color, _T("PLAYER_HP  : %d"), iplayer_data->GetHitPoint(tag));
		SpriteBatch.DrawString(player_date, power_pos + Vector2(0, 60), text_color, _T("PLAYER_SPD : %d"), iplayer_data->GetSpeed(tag));
	}
}
//攻撃、hp、スピード
