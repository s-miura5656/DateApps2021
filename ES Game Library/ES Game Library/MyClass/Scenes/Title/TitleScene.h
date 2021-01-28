#pragma once

#include "../BaseScene.h"
#include"../../Managers/InputManager/InputManager.h"
#include"../../Data/ImpactSpeed.h"

class TitleScene : public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override {}
	int TitleLanding();
	int OperationButton();
	void DemoMove();


private:
	//! file
	SPRITE _title_logo;
	SPRITE _background;
	SPRITE _robot;
	SPRITE _operation_button;
	SPRITE _tutorial;

	MEDIA _demo_movie;
	

	float _title_logo_alpha;
	float _operation_button_alpha;
	int _demo_scene_count;
	int _play_count;
	bool _movie_flag;

	//! flag
	bool _button_flashing_flag;
	bool _button_push_flag;
	bool _tutorial_flag;
	bool _demo_move_flag;

	Vector3 _title_logo_position;
	Vector2 _title_logo_scale;
	Vector2 _operation_button_scale;
};