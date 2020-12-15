#pragma once

#include "../BaseScene.h"
#include"../../Managers/ControllerManager/ContorollerManager.h"
#include"../../Data/ImpactSpeed.h"


class TitleScene : public BaseScene
{
public:
	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override {}

	float Flashing();
	float Scaling();

private:
	SPRITE _title;
	SPRITE _background;
	SPRITE _robot;
	SPRITE _b_button;

	SPRITE _sprite;

	float sprite_alpha;
	bool alpha_flag;
	bool button_flag;

	Vector3 title_pos;

	Vector3 sprite_pos;
	Vector2 sprite_scale;

	enum {MODEL_MAX = 5};
	MODEL model[MODEL_MAX];
	CAMERA camera;

	MODEL item;

	float _scale = 1.f;

	float _alpha = 1.f;

	float _wave = 1.f;

	float _bound = 5.f;


	ImpactSpeed impactspeed;
	
};