#pragma once

#include "../../../ESGLib.h"

class MainScene;
class TitleScene;
class ResultScene;
class BaseScene;

class SceneManager
{
public:
	enum SceneState
	{
		TITLE,
		MAIN,
		RESULT
	};


	SceneManager();
	~SceneManager();

	void ChangeScene(SceneState scene);

	bool Initialize();
	int Update();
	void Draw2D();
	void Draw3D();

	static SceneManager& Instance() {
		static SceneManager instance;
		return instance;
	};

private:
	SceneManager(const SceneManager&) = delete;
	void operator=(const SceneManager&) = delete;

	MainScene* _main_scene;
	TitleScene* _title_scene;
	ResultScene* _result_scene;

	BaseScene* _scene;
};