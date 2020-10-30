#pragma once

#include "../BaseScene.h"

class TitleScene : public BaseScene
{
public:
	bool Initialize();
	int Update();
	void Draw2D();
	void Draw3D();
private:
	SPRITE _title;
};