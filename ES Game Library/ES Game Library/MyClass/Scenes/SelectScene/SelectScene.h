#pragma once

#include "../BaseScene.h"
#include "../../Data/WordsTable.h"

class SelectScene : public BaseScene
{
public:
	SelectScene();
	~SelectScene();
	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override {}

private:

	EFFECT _shader;
	SPRITE _texture[PLAYER_COUNT_MAX];

	ANIMATIONMODEL _player_model;

	int _chara_select[PLAYER_COUNT_MAX];
	float _player_position[PLAYER_COUNT_MAX];


	bool _select_complete_flag;
	enum 
	{
		RED,
		BLUE,
		GREEN,
		YELLOW
	};
};