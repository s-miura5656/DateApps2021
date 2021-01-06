#pragma once
#include "../../../ESGLib.h"
#include "../../Data/IData.h"

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

	static SPRITE  score_font;//各プレイヤーのスコア
	int score;
	int prev_rank_point;
	Vector3 corner[2];
	int add_point;
	int delta_point;
	
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

	bool Initialize(LPCTSTR banner_name, const Vector3& banner_pos);
	int  Update();
	void Draw2D();
	void RegisterPointAnimation(Vector3 player_num);
	void MovePointAnimation(Vector3 player_num);
};