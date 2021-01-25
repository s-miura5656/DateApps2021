#include "PointAnimation.h"

PointAnimation::PointAnimation()
{
}

PointAnimation::~PointAnimation()
{
}

void PointAnimation::RegisterPointAnimation(Vector3 player_pos)
{
	//auto rank_point = _i_player_data->GetRankingPoint(tag);

	////! ポイントを入手した時
	//if (rank_point > prev_rank_point)
	//{
	//	auto pointAnim = PointMove();
	//	pointAnim.point = rank_point - prev_rank_point;
	//	pointAnim.position = player_pos;
	//	pointAnim.theta = 0.0f;
	//	pointAnim.alpha = 1.0f;
	//	pointMove.push_back(pointAnim);
	//}
	//prev_rank_point = rank_point;
}

void PointAnimation::MovePointAnimation(Vector3 player_pos)
{
//	if (pointMove.size() == 0)
//	{
//		return;
//	}
//	//! 入手ポイントの移動
//	for (int i = 0; i < pointMove.size(); ++i)
//	{
//		Vector3 bezier = Vector3_Bezier(player_pos, corner[0], corner[0], banner_position + Vector3(100, 40, 0), pointMove[i].theta);
//		Vector3 bezier2 = Vector3_Bezier(player_pos, corner[1], corner[1], banner_position + Vector3(0, 0, 0), pointMove[i].theta);
//		pointMove[i].theta += 0.008;
//
//		//! 1pと2pのベジェ曲線
//		if (player_index == 0 || player_index == 1) {
//			pointMove[i].position.y = bezier.y;
//			pointMove[i].position.x = bezier.x;
//		}
//
//		//! 3pと4pのベジェ曲線
//		if (player_index == 2 || player_index == 3) {
//			pointMove[i].position.y = bezier2.y;
//			pointMove[i].position.x = bezier2.x;
//		}
//
//		pointMove[i].alpha -= 0.003;
//
//		//! バナーの座標に入手したポイントがたどり着いたとき 1p & 3p
//		if (player_index == 0 || player_index == 2) {
//			if (pointMove[i].position.x <= banner_position.x + 100) {
//				add_point += pointMove[i].point;
//				_font_size = 0.6 + ((float)(add_point - score) / (float)1000);
//				delta_point = (add_point - score) / GameTimer.GetFPS() * 4;
//				pointMove.erase(pointMove.begin() + i);
//			}
//		}
//
//		//! バナーの座標に入手したポイントがたどり着いたとき 2p & 4p
//		if (player_index == 1 || player_index == 3) {
//			if (pointMove[i].position.x >= banner_position.x + 100) {
//				add_point += pointMove[i].point;
//				_font_size = 0.6 + ((float)(add_point - score) / (float)1000);
//				delta_point = (add_point - score) / GameTimer.GetFPS() * 4;
//				pointMove.erase(pointMove.begin() + i);
//			}
//		}
//	}
}
