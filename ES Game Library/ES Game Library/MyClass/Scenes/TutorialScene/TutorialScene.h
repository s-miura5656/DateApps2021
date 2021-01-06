#pragma once

#include "../BaseScene.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"

class TutorialScene : public BaseScene
{
public:
	TutorialScene();
	~TutorialScene();
	bool Initialize() override;
	int  Update() override;
	void Draw2D() override;
	void Draw3D() override {}
	void DrawAlpha3D() override {}

private:

	SPRITE _tutorial;

};