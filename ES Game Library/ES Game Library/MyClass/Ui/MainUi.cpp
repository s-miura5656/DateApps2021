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
	HP_green = GraphicsDevice.CreateSpriteFromFile(_T("HpSprite/緑.png"));
	HP_red = GraphicsDevice.CreateSpriteFromFile(_T("HpSprite/ゲージベース2.png"));
	HP_black = GraphicsDevice.CreateSpriteFromFile(_T("HpSprite/ゲージベース.png"));

	for (int i = 0; i < 4; ++i) {
		green_x[i] = 320.0f;
		red_x[i] = 320.0f;
	}
	/*hp_bar  = RectWH(0.0f, 0.0f, green_x * hit_points / 300.0f, 22);
	red_bar = RectWH(0.0f, 0.0f, red_x, 22);*/

	powor_ui_pos[0] = Vector2(  10,   0);
	powor_ui_pos[1] = Vector2(950,   0);
	powor_ui_pos[2] = Vector2(  10, 620);
	powor_ui_pos[3] = Vector2(950, 620);
	
	hp_ui_pos[0] = Vector3(  10,  30,0);
	hp_ui_pos[1] = Vector3(950,  30,0);
	hp_ui_pos[2] = Vector3(  10, 650,0);
	hp_ui_pos[3] = Vector3(950, 650,0);

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
	SpriteBatch.DrawString(time_limit_font, Vector2(530, 0), Color(1.f, 1.f, 1.f), _T("TIME : %d"), int(TimeManager::Instance().GetTimeLeft()));
	DebugDraw();
	HpAnimation();
}

#ifdef _DEBUG
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
#endif
void MainUi::HpAnimation()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string& tag = PLAYER_TAG + std::to_string(i + 1);
		auto hp = iplayer_data->GetHitPoint(tag);

		if (green_x[i] * hp / 1000.0f < red_x[i]) {
			red_x[i] -= 2;
		}

		RectWH hp_bar  = RectWH(0.0f, 0.0f, green_x[i] * hp / 1000.0f, 22);
		RectWH red_bar = RectWH(0.0f, 0.0f, red_x[i], 22);

		SpriteBatch.Draw(*HP_green, hp_ui_pos[i] , hp_bar);
		SpriteBatch.Draw(*HP_red,   hp_ui_pos[i] + Vector3(0, 0, 1), red_bar);
		SpriteBatch.Draw(*HP_black, hp_ui_pos[i] + Vector3(0, 0, 2));
	}

}

void MainUi::SetDamege(const int player_number, const int damage)
{
	green_x[player_number] -= damage;
	if (green_x[player_number] < 0)
		green_x[player_number] = 0;
}

//攻撃、hp、スピード
