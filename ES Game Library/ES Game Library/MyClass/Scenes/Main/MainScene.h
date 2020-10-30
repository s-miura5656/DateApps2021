#pragma once

#include "../../../ESGLib.h"

class MainScene
{
public:
	MainScene();
	~MainScene();

	bool FileInitialize();
	bool Initialize();
	int Update();
	void Draw2D();
	void Draw3D();

private:

};