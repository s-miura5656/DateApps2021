#pragma once

#include "../BaseScene.h"
#include"../../Managers/ControllerManager/ContorollerManager.h"
#include"../../Data/ImpactSpeed.h"


class TitleScene : public BaseScene
{
public:
	bool Initialize();
	int Update();
	void Draw2D();
	void Draw3D();

	float Flashing();
	float Scaling();

private:
	SPRITE _title;
	SPRITE _sprite;

	float sprite_alpha;

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