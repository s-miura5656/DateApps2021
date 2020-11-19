#pragma once
#include "../../ESGLib.h"
#include"../Ui/BaseUi.h"
#include "../Data/WordsTable.h"

class MainUi : public BaseUi
{
private:

public:
	MainUi();
	~MainUi();

	
	bool Initialize() override;
	int Update() override { return 0; }
	void Draw2D() override;
#ifdef _DEBUG
	void DebugDraw(PlayerBase* player) override;
#endif

	FONT player_date;//各プレイヤーのステータス表記
	Vector2 powor_ui_pos[PLAYER_COUNT_MAX];//各プレイヤーのパワー
	Vector2 hp_ui_pos[PLAYER_COUNT_MAX];//各プレイヤーの㏋
	Vector2 speed_ui_pos[PLAYER_COUNT_MAX];//各プレイヤーのスピード

	Color color[PLAYER_COUNT_MAX];//各プレイヤーの色指定

	SPRITE hp;
	RectWH hp_;
	float hp_x, hp_y;


};