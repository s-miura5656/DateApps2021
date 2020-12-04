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

private:
	SPRITE _title;

	enum {MODEL_MAX = 5};
	MODEL model[MODEL_MAX];
	CAMERA camera;

	MODEL item;

	//Vector3 impact;
	//Vector3 attenuate;

	float _scale = 1.f;

	float _alpha = 1.f;

	float _wave = 1.f;

	float _bound = 5.f;


	ImpactSpeed impactspeed;
};