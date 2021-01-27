#include "PointAnimation.h"
#include "../../Data/IData.h"

PointAnimation::PointAnimation()
{
}

PointAnimation::~PointAnimation()
{
}

void PointAnimation::RegisterPointAnimation(Vector3 player_pos, std::string tag, int prev_rank_point)
{
	auto rank_point = _i_player_data->GetRankingPoint(tag);

	//! ポイントを入手した時
	if (rank_point > prev_rank_point)
	{
		auto pointAnim = PointMove();
		pointAnim.point = rank_point - prev_rank_point;
		pointAnim.position = player_pos;
		pointAnim.theta = 0.0f;
		pointAnim.alpha = 1.0f;
		pointMove.push_back(pointAnim);

		for (int i = 0; i < pointMove.size(); ++i) {
			add_point += pointMove[i].point;
			_font_size = 0.5 + ((float)(add_point - score) / (float)1000);
			delta_point = (add_point - score) / GameTimer.GetFPS() * 4;
		}
	}
	prev_rank_point = rank_point;
}

void PointAnimation::MovePointAnimation(Vector3 player_pos)
{
	if (pointMove.size() == 0)
	{
		return;
	}
	//! 入手ポイントの移動
	for (int i = 0; i < pointMove.size(); ++i)
	{
		Vector3 bezier = Vector3_Bezier(player_pos + Vector3(-80, -50, 0), player_pos + Vector3(-80, -60, 0),
			player_pos + Vector3(-80, -60, 0), player_pos + Vector3(-80, -80, 0), pointMove[i].theta);
		pointMove[i].theta += 0.008;

		pointMove[i].position.y = bezier.y;
		pointMove[i].position.x = bezier.x;

		pointMove[i].alpha -= 0.03;

		if (pointMove[i].position.x <= player_pos.y - 81) {
			pointMove.erase(pointMove.begin() + i);
		}

	}
}
	
