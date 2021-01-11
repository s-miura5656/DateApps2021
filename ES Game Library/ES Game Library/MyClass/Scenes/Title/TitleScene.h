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
	int TitleLanding();
	int OperationButton();


private:
	//! file
	SPRITE _title_logo;
	SPRITE _background;
	SPRITE _robot;
	SPRITE _operation_button;
	SPRITE _tutorial;
	

	float title_logo_alpha;
	float operation_button_alpha;
	int demo_scene_count;

	//! flag
	bool button_flashing_flag;
	bool button_push_flag;
	bool tutorial_flag;
	bool demo_scene_flag;

	Vector3 title_logo_position;
	Vector2 title_logo_scale;
	Vector2 operation_button_scale;
};