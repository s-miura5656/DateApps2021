#pragma once

#include "../BaseScene.h"
#include"../../Managers/ControllerManager/ContorollerManager.h"
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

private:
	SPRITE _title;
	SPRITE _background;
	SPRITE _robot;
	SPRITE _b_button;
	SPRITE _tutorial;

	float button_alpha;
	bool  alpha_flag;
	bool  button_flag;
	bool  tutorial_flag;

	Vector3 title_pos;
	Vector2 title_scale;
	Vector2 button_scale;

	float _scale = 1.f;
	float _alpha = 1.f;
	float _wave  = 1.f;
	float _bound = 5.f;
};