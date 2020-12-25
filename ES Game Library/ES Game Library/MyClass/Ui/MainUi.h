#pragma once
#include "../../ESGLib.h"
#include"../Ui/BaseUi.h"
#include "../Data/WordsTable.h"
#include"../Data/IData.h"
#include"../Ui/PlayerUi.h"

class MainUi : public BaseUi
{
private:

public:
	MainUi();
	~MainUi();

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	
	std::vector<PlayerUi> player_ui;
	std::unique_ptr<IPrayerData> _i_player_data;
	std::unique_ptr<IArmData> _i_arm_data;

	FONT player_date;//各プレイヤーのステータス表記

	Vector2 score_pos[PLAYER_COUNT_MAX];//各プレイヤーのスコア

	Vector2 speed_ui_pos[PLAYER_COUNT_MAX];//各プレイヤーのスピード

	Color color[PLAYER_COUNT_MAX];//各プレイヤーの色指定

	SPRITE time_banner;

	FONT time_limit_font;

	FONT back_count;
	FONT front_count;

	int move_flag;
};