#pragma once

#include "../BaseScene.h"
#include"../../Managers/ControllerManager/ContorollerManager.h"
#include"../../Data/IData.h"
class ResultScene : public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	bool Initialize();
	int Update();
	void Draw2D();
	void Draw3D();
private:
	SPRITE ground;
	SPRITE champion;
	SPRITE totitle;
	FONT txt;
	int num;
	ANIMATIONMODEL model;
	CAMERA camera;
	IPrayerData* _i_player_data;

	EFFECT _shader;
	SPRITE _texture;
};