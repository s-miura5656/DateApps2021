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
	void DebugDraw();
	void HpAnimation();
	void SetDamege(const int player_number, const int damage);

	FONT player_date;//各プレイヤーのステータス表記
	Vector2 powor_ui_pos[PLAYER_COUNT_MAX];//各プレイヤーのパワー
	Vector3 hp_ui_pos[PLAYER_COUNT_MAX];//各プレイヤーの㏋
	Vector2 speed_ui_pos[PLAYER_COUNT_MAX];//各プレイヤーのスピード

	Color color[PLAYER_COUNT_MAX];//各プレイヤーの色指定

	//HPアニメーション
	SPRITE HP_green;
	SPRITE HP_red;
	SPRITE HP_black;
	
	float green_x[PLAYER_COUNT_MAX];
	float red_x[PLAYER_COUNT_MAX];

};