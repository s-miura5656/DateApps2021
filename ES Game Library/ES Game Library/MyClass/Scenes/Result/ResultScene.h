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

	double _animation_count = 0;

	void                  ArrivalCount();
	int                   GetRankNum(int);
	int                   GetPoints(int);
	SPRITE                _player_rank_num;
	SPRITE                _background;
	SPRITE                _totitle;
	SPRITE                _player_first_ground;
	SPRITE                _robot_win;
	SPRITE                _light;
	SPRITE                _robot_fece;
	SPRITE                _texture;
	SPRITE                _score_sprite;
	SPRITE                _first_score_sprite;
	EFFECT                _shader;
	ANIMATIONMODEL        _player_model;
	int                   _arrival_count;
	int                   _random_number = 0;
	float                 _acceleration[PLAYER_COUNT_MAX - 1];
	float                 _small_score_scale[PLAYER_COUNT_MAX - 1];
	float                 _big_score_scale;
	Vector3               _background_position;
	std::vector<Vector3>  _player_rank_num_position;
	std::vector<int>      _player_rectwh;
};