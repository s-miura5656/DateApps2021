#pragma once

#include "../BaseScene.h"
#include"../../Data/IData.h"

class ResultScene : public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	bool Initialize() override;
	int  Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override {}

private:
	void    ArrivalCount();
	int     GetRankNum(int);
	int     GetPoints(int);
	float   PlayerScaleCalculation(int);
	Vector3 PlayerPositionCalculation(int);
	Vector3 PlayerRankNumberPositionCalculation(int);
	Vector2 TextSizeCalculation(int);
	Vector2 PointTextPosition(int);
	SPRITE  player_rank_num;
	SPRITE  background;
	SPRITE  totitle;
	EFFECT                shader;
	ANIMATIONMODEL player_model;
	FONT font;
	int  arrival_count;
	float                 _player_model_big_scale;
	float                 _player_model_small_scale;
	Vector2               _text_big_size;
	Vector2               _text_small_size;
	Vector2               _point_big_text_position;
	Vector2               _point_small_text_position;
	Vector3               _player_big_position;
	Vector3               _player_small_position;
	Vector3               _background_position;
	Vector3               _totitle_position;
	float                 _player_big_position_x;
	float                 _player_small_position_x;
	float                 _player_rank_number_position_x;
	float                 _player_rank_number_position_y;
	float                 _point_big_text_position_x;
	float                 _point_small_text_position_x;
	std::vector<Vector3> player_rank_num_position;
	IPrayerData* i_player_data;
	std::vector<SPRITE>texture;
};