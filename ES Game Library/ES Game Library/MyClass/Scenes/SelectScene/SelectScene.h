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
	bool GameStart();

	enum { TEXTURE_MAX = 7 };

	EFFECT _shader;
	SPRITE _texture[TEXTURE_MAX];
	SPRITE _bg_sprite;
	SPRITE _banner;
	SPRITE _button_ready;
	SPRITE _button_go;
	SPRITE _chara_frame;
	SPRITE _button_frame;
	SPRITE _left_arrow;
	SPRITE _left_arrow_dark;
	SPRITE _right_arrow;
	SPRITE _right_arrow_dark;
	ANIMATIONMODEL _player_model;

	int _select_count = 0;

	int _chara_select[PLAYER_COUNT_MAX];
	float _player_position[PLAYER_COUNT_MAX];
	float _player_rotation[PLAYER_COUNT_MAX];
	bool _player_button_flag[PLAYER_COUNT_MAX];
	bool _left_arrow_flag[PLAYER_COUNT_MAX];
	bool _right_arrow_flag[PLAYER_COUNT_MAX];
	bool _select_complete_flag[PLAYER_COUNT_MAX];
	bool _game_start_flag = true;
	bool _player_rotation_flag[PLAYER_COUNT_MAX];

	enum
	{
		RED,
		BLUE,
		GREEN,
		YELLOW,
		LIGHTBLUE,
		PINK,
		PURPLE
	};
};