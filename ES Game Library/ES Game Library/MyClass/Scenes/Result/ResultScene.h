#pragma once

#include "../BaseScene.h"
#include"../../Managers/ControllerManager/ContorollerManager.h"

class ResultScene : public BaseScene
{
public:
	bool Initialize();
	int Update();
	void Draw2D();
	void Draw3D();
private:
	SPRITE ground;
	SPRITE champion;
	SPRITE totitle;
	MODEL model;
	CAMERA camera;
};