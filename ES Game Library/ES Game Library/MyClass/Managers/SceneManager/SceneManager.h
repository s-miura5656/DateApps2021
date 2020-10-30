#pragma once

#include "../../../ESGLib.h"

class MainScene;
class TitleScene;
class ResultScene;

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
	TitleScene* _title_scene;
	ResultScene* _result_scene;
};