#pragma once

#include "../BaseScene.h"
#include"../../Managers/ControllerManager/ContorollerManager.h"
#include"../../Data/IData.h"
<<<<<<< HEAD

=======
#include"../../Managers/SceneManager/SceneManager.h"
>>>>>>> cf893e710f413e5dde5084f45cb4a2ee7ff9259e
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
	int arrival;
	int fix;
	std::vector<Vector3> pos;
	ANIMATIONMODEL model;
	IPrayerData* _i_player_data;
	EFFECT _shader;
	std::vector<SPRITE>_texture;
};