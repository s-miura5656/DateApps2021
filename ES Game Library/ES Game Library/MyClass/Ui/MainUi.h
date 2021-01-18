#pragma once
#include "../../ESGLib.h"
#include "../Ui/BaseUi.h"
#include "../Data/WordsTable.h"
#include "../Ui/PlayerUI/PlayerUi.h"

class IPrayerData;
class IArmData;

class MainUi : public BaseUi
{
private:

public:
	MainUi();
	~MainUi();

	bool Initialize() override;
	int Update()	  override;
	void Draw2D()	  override;
	
	PlayerUi* player_ui[4];

	//IPrayerData* _i_player_data;

	//IArmData* _i_arm_data;

	//std::vector<PlayerUi*> player_ui;

	//FONT player_date;//各プレイヤーのステータス表記

	//Vector2 score_pos[PLAYER_COUNT_MAX];//各プレイヤーのスコア

	//Vector2 speed_ui_pos[PLAYER_COUNT_MAX];//各プレイヤーのスピード

	//Color color[PLAYER_COUNT_MAX];//各プレイヤーの色指定

	//SPRITE time_banner;//タイムバナー
	//Vector3 time_banner_pos;
	//Vector3 minutes_pos;
	//Vector3 tens_place_pos;
	//Vector3 ones_place_pos;
	//

	//SPRITE number_sprite;//数字
	//RectWH number[10];



	//Color black;//黒
	//Color White;//白

	//FONT time_limit_font;
	//Vector3 Countdown_pos;

	//FONT back_count;
	//FONT front_count;

	//int move_flag;
};