#pragma once

#include "../../../ESGLib.h"

class MainScene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	bool FileInitialize();
	bool Initialize();
	int Update();
	void Draw2D();
	void Draw3D();

private:
	MainScene* _main_scene;
};