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
	void ColorBlinking();
	void TimeSizeFluctuation();

	
	IPrayerData* _i_player_data;

	IArmData* _i_arm_data;

	std::vector<PlayerUi*> player_ui;

	FONT player_date;//各プレイヤーのステータス表記

	Vector2 score_pos[PLAYER_COUNT_MAX];//各プレイヤーのスコア

	Vector2 speed_ui_pos[PLAYER_COUNT_MAX];//各プレイヤーのスピード

//	Color color[PLAYER_COUNT_MAX];//各プレイヤーの色指定

	SPRITE time_banner;//タイムバナー
	Vector3 time_banner_pos;
	Vector3 minutes_pos;
	Vector3 tens_place_pos;
	Vector3 ones_place_pos;
	Vector3 colon_pos;
	
	/*Vector2 minutes_pos_v2_b;
	Vector2 tens_place_pos_v2_b;
	Vector2 ones_place_pos_v2_b;

	Vector2 minutes_pos_v2_w;
	Vector2 tens_place_pos_v2_w;
	Vector2 ones_place_pos_v2_w;*/

	SPRITE number_sprite;//数字
	RectWH number[11];

	SPRITE start_end;
	bool s_or_e;
	RectWH start_end_rect[2];

	Color Danger;//赤点滅
	bool Blinking;
	int r, g, b;

	float time_size_up;
	float time_size_down;
	bool time_size_pp;
	bool time_size_flag;

	Color black;//黒
	Color White;//白

	FONT time_limit_font;
	Vector3 Countdown_pos;
	float cout_size;
	int rt;

	FONT back_count;
	FONT front_count;

	int move_flag;
	float font_size;
	bool time_limit_decreasing;

	int old_time;
	float end_a;
	float font_size_e;
	
	float start_size;
	float start_a;
	float finsh_size;
	float finsh_a;
	bool a_and_e;
};