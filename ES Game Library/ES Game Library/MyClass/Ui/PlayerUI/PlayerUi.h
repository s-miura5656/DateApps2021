#pragma once
#include "../../../ESGLib.h"
#include "../../Data/IData.h"
#include "../../Managers/TimeManager/Time.h"

struct PointAnimation
{
	Vector3 position;
	float theta;
	int point;
	float alpha;
	PointAnimation()
	{
		position = Vector3_Zero;
		theta = 0.0f;
		point = 0;
		alpha = 0;
	}
};

class PlayerUi
{
private:
	int player_index;//プレイヤーナンバー
	std::string tag;
	std::string _arm_tag;

	Vector3 banner_position;//各プレイヤーのバナー
	SPRITE  banner_sprite;//各プレイヤーのバナー
	SPRITE  banner_sprite_2;
	Vector3 icon_pos_n1;
	Vector3 icon_pos;
	SPRITE  banner_status;//各プレイヤーのバナー
	SPRITE  item_icon;//各プレイヤーのバナー
	RectWH  banner_rw;
	SPRITE  joy_icon;
	SPRITE  normal_icon;
	Vector3 player_pos;
	SPRITE  ranking;

	static SPRITE  score_font;//各プレイヤーのスコア
	int score;
	int prev_rank_point;
//	Vector3 corner[2];
	int add_point;
	int delta_point;
//	int lost_point;
	float _font_size = 0.6;
//	bool lost_flag;

	int ranking_timer;
	
	std::vector<PointAnimation> pointAnimation;

	Vector2 player_position;//各プレイヤーの位置
	static FONT player_font;

	static SPRITE test;

	std::vector<Vector3> move_pos;

	std::unique_ptr<IPrayerData> _i_player_data;
	std::unique_ptr<IArmData>    _i_arm_data;
public:
	PlayerUi() {}
	PlayerUi(const int player_no);
	~PlayerUi();

	bool Initialize(const Vector3& banner_pos, RectWH banner_rectWH);
	int  Update();
	void Draw2D();
	void RegisterPointAnimation(Vector3 player_num);
	void MovePointAnimation(Vector3 player_num);
};