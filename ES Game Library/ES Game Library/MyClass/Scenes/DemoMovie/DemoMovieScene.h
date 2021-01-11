#pragma once

#include "../BaseScene.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"

class DemoMovieScene : public BaseScene
{
public:
	DemoMovieScene();
	~DemoMovieScene();
	bool Initialize() override;
	int  Update() override;
	void Draw2D() override;
	void Draw3D() override {}
	void DrawAlpha3D() override {}


private:

	SPRITE _operation_button;
	MEDIA  _demo_movie;

	float operation_button_alpha;
	int   replay_count;

	bool  button_flashing_flag;
	bool  movie_replay_flag;

	Vector2 operation_button_scale;

};

