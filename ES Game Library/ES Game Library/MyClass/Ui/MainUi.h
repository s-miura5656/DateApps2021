#pragma once
#include "../../ESGLib.h"
#include"../Ui/BaseUi.h"
#include "../Data/WordsTable.h"
#include"../Data/IData.h"

class MainUi : public BaseUi
{
private:

public:
	MainUi();
	~MainUi();

	
	bool Initialize() override;
	int Update() override { return 0; }
	void Draw2D() override;
	void PlayerBanner();
	void PointAnimation();
	

	FONT player_date;//各プレイヤーのステータス表記

	Vector3 banner_pos[PLAYER_COUNT_MAX];//各プレイヤーのバナー
	Vector2 score_pos[PLAYER_COUNT_MAX];//各プレイヤーのスコア

	Vector2 speed_ui_pos[PLAYER_COUNT_MAX];//各プレイヤーのスピード

	Color color[PLAYER_COUNT_MAX];//各プレイヤーの色指定

	SPRITE red_banner;
	SPRITE blue_banner;
	SPRITE green_banner;
	SPRITE yellow_banner;

	SPRITE time_banner;

	SPRITE score_num;

	FONT score_data[PLAYER_COUNT_MAX];
	IPrayerData* i_player_data;
	IArmData* i_arm_data;

	FONT kuro;
	FONT siro;

	//test
	SPRITE test;
	int flag;
	Vector3 point_pos;

};