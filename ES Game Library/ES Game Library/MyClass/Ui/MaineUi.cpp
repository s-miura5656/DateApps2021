#include"MaineUi.h"
#include "../Data/GameData.h"
#include "../Managers/TimeManager/Time.h"

MaineUi::MaineUi()
{
	iplayer_data = new IPrayerData;
}

MaineUi::~MaineUi()
{

}


bool MaineUi::Initialize()
{
	time_limit_font = GraphicsDevice.CreateSpriteFont(_T("SketchFlow Print"), 50);
	player_date = GraphicsDevice.CreateSpriteFont(_T("SketchFlow Print"), 50);
	hp = GraphicsDevice.CreateSpriteFromFile(_T("ゲージベース2.png"));

	hp_x =1000.0f;
	hp_y = 25.0f;

	powor_ui_pos[0] = Vector2(0,0) ;
	powor_ui_pos[1] = Vector2(800, 0);
	powor_ui_pos[2] = Vector2(0, 550);
	powor_ui_pos[3] = Vector2(800,550);
	
	hp_ui_pos[0] = Vector3(0, 50,0);
	hp_ui_pos[1] = Vector3(800, 50,0);
	hp_ui_pos[2] = Vector3(0, 600,0);
	hp_ui_pos[3] = Vector3(800, 600,0);

	speed_ui_pos[0] = Vector2(0, 100);
	speed_ui_pos[1] = Vector2(800, 100);
	speed_ui_pos[2] = Vector2(0, 650);
	speed_ui_pos[3] = Vector2(800, 650);

	color[0] = Color(255, 0  , 0);
	color[1] = Color(0  , 255, 0);
	color[2] = Color(0  ,  0 ,255);
	color[3] = Color(255, 255,  0);

	InputDevice.CreateKeyboard();

	return true;
}

int MaineUi::Update()
{
	KeyboardState key = Keyboard->GetState();
	if (key.IsKeyDown(Keys_Space)) {
		hp_x -= 10;
	}
	
	return 0;
}

void MaineUi::Draw2D()
{
	SpriteBatch.DrawString(time_limit_font, Vector2(0, 300), Color(0, 0, 255), _T("リアルタイム:%d"), (TimeManager::Instance().time));

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		auto name = PLAYER_TAG + to_string(i + 1);

		SpriteBatch.DrawString(player_date, powor_ui_pos[i], Color(color[i]), _T("player_Powor:%d"), iplayer_data->GetAttackPowor(name));
		/*SpriteBatch.DrawString(player_date, hp_ui_pos[i], Color(color[i]), _T("player_HitPoint:%d"), iplayer_data->GetHitPoint(name));*/
		SpriteBatch.DrawString(player_date, speed_ui_pos[i], Color(color[i]), _T("player_Speed:%d"), iplayer_data->GetSpeed(name));

		iplayer_data->SetHitPoint(name, hp_x);
		SpriteBatch.Draw(*hp, Vector3(hp_ui_pos[i]), RectWH(0, 0, 320*iplayer_data->GetHitPoint(name)/1000.0f, 25));//hpアニメーション
	}
	
}
//攻撃、hp、スピード
