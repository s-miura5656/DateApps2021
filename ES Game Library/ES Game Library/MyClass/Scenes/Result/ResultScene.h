#pragma once

#include "../BaseScene.h"
#include"../../Data/IData.h"

class ResultScene : public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override {}

private:
	void ArrivalCount();
	int GetRankNum(int);
	int GetPoints(int);
	float PlayerScaleCalculation(int);
	Vector3 PlayerPositionCalculation(int);
	Vector3 PlayerRankNumberPositionCalculation(int);
	Vector2 TextSizeCalculation(int);
	Vector2 PointTextPosition(int);
	SPRITE player_rank_num;
	SPRITE background;
	SPRITE totitle;
	EFFECT shader;
	ANIMATIONMODEL player_model;
	FONT font;
	int arrival_count;
	std::vector<Vector3> player_rank_num_position;
	IPrayerData* i_player_data;
	std::vector<SPRITE>texture;
};