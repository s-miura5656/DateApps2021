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
	void                  ArrivalCount();
	int                   GetRankNum(int);
	int                   GetPoints(int);
	float                 PlayerScaleCalculation(int);
	Vector3               PlayerPositionCalculation(int);
	Vector3               PlayerRankNumberPositionCalculation(int);
	Vector2               TextSizeCalculation(int);
	Vector2               PointTextPosition(int);
	SPRITE                _player_rank_num;
	SPRITE                _background;
	SPRITE                _totitle;
	EFFECT                _shader;
	ANIMATIONMODEL        _player_model;
	FONT                  _font;
	int                   _arrival_count;
	float                 _player_model_big_scale;
	float                 _player_model_small_scale;
	float                 _player_big_position_x;
	float                 _player_small_position_x;
	float                 _point_big_text_position_x;
	float                 _point_small_text_position_x;
	Vector2               _text_big_size;
	Vector2               _text_small_size;
	Vector2               _point_big_text_position;
	Vector2               _player_rank_number_position;
	Vector2               _point_small_text_position;
	Vector3               _player_big_position;
	Vector3               _player_small_position;
	Vector3               _background_position;
	Vector3               _totitle_position;
	std::vector<SPRITE>   _texture;
	std::vector<Vector3>  _player_rank_num_position;
};