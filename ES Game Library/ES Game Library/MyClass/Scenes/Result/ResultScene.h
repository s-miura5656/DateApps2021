#pragma once

#include "../BaseScene.h"
#include"../../Managers/ControllerManager/ContorollerManager.h"
#include"../../Data/IData.h"
class ResultScene : public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override {}

private:
	SPRITE player;
	SPRITE ground;
	SPRITE totitle;
	FONT txt;
	int num;
	ANIMATIONMODEL model;
	CAMERA camera;
	IPrayerData* _i_player_data;

	EFFECT _shader;
	SPRITE _texture;
};