#pragma once
#include "../../../ESGLib.h"
#include "../../Data/IData.h"
#include "../../Managers/TimeManager/Time.h"
#include "../BaseUi.h"
#include "../../Data/IData.h"
#include <string>

using namespace std;

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

class PlayerUi : public BaseUi
{
public:
	PlayerUi() {}
	PlayerUi(int player_no);
	~PlayerUi();

	Vector3 player_pos;
	//void RegisterPointAnimation(Vector3 player_num);
	//void MovePointAnimation(Vector3 player_num);

	bool Initialize(int player);
	bool Initialize() override { return true; };
	int Update()	  override;
	void Draw2D()	  override;

private:
	int player_index;//プレイヤーナンバー
	std::string tag;
	
	Vector3 _banner_pos;//各プレイヤーのバナー
	SPRITE  _banner_sprite;//各プレイヤーのバナー
	RectWH  _banner_rw;

	Vector3 _player_icon_pos;
	SPRITE _player_icon;//各プレイヤーのアイコン
	RectWH _player_joy_icon_rw;
	RectWH _player_normal_icon_rw;

	Vector3  _banner_status_pos;
	SPRITE  _banner_status;//各プレイヤーのステータスバナー
	RectWH  _status_rw;

	SPRITE  _item_icon;//各プレイヤーのステータスアイコン

	enum RANKING //順位
	{ FIRST, SECOND, THIRD, FOURTH };
	SPRITE  ranking;
	

	static SPRITE  score_font;//各プレイヤーのスコア
	int score;
	float _font_size;
	//int prev_rank_point;
	//Vector3 corner[2];
	//int add_point;
	//int delta_point;
	//int lost_point;
	
	//bool lost_flag;

	//int ranking_timer;
	//
	//std::vector<PointAnimation> pointAnimation;

	//Vector2 player_position;//各プレイヤーの位置
	//static FONT player_font;

	//static SPRITE test;

	//std::vector<Vector3> move_pos;

	IPrayerData* _i_player_data;
	

	//void RegisterPointAnimation(Vector3 player_num);
	//void MovePointAnimation(Vector3 player_num);
};