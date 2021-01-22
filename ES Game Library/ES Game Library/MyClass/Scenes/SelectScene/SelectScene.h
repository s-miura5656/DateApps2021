#pragma once

#include "../BaseScene.h"
#include "../../Data/WordsTable.h"

class BaseInput;
class PlayerTexture;

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

	void ColorSelect(int player_number, BaseInput* pad);

	enum { TEXTURE_MAX = 8 };

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

	std::vector<PlayerTexture*> _textures;
	//int _banners[TEXTURE_MAX];


	int _select_count[PLAYER_COUNT_MAX];

	float _banner_color[PLAYER_COUNT_MAX];
	int _chara_select_seve[PLAYER_COUNT_MAX];
	int _chara_select[PLAYER_COUNT_MAX];
	float _player_position[PLAYER_COUNT_MAX];
	float _player_rotation[PLAYER_COUNT_MAX];
	bool _player_button_flag[PLAYER_COUNT_MAX];
	bool _left_arrow_flag[PLAYER_COUNT_MAX];
	bool _right_arrow_flag[PLAYER_COUNT_MAX];
	bool _select_complete_flag[PLAYER_COUNT_MAX];
	bool _game_start_flag = false;
	bool _player_rotation_flag[PLAYER_COUNT_MAX];

	enum
	{
		RED,
		BLUE,
		GREEN,
		YELLOW,
		LIGHTBLUE,
		ORANGE,
		LIGHTGREEN,
		PURPLE
	};
};

class PlayerTexture
{
public:
	PlayerTexture() {};
	~PlayerTexture() {};

	void SetTexture(SPRITE texture) { _texture = texture; }
	SPRITE GetTexture() const { return _texture; }

	void SetFlag(bool flag) { _flag = flag; }
	bool IsFlag() const { return _flag; }

private:
	SPRITE _texture = nullptr;
	bool _flag = false;
};