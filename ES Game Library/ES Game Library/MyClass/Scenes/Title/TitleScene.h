#pragma once

#include "../BaseScene.h"
#include"../../Managers/ControllerManager/ContorollerManager.h"


class TitleScene : public BaseScene
{
public:
	bool Initialize();
	int Update();
	void Draw2D();
	void Draw3D();

private:
	SPRITE _title;
	MODEL model[4];
	CAMERA camera;

	MODEL item;


	float _scale = 1.f;

	float _alpha = 1.f;

	float _wave = 1.f;

	float _bound = 5.f;
};