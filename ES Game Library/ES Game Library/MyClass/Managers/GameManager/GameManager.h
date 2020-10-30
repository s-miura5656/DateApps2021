#pragma once

#include "../../../ESGLib.h"
#include "../SceneManager/SceneManager.h"

class SceneManager;

enum SceneState
{
	TITLE,
	MAIN,
	RESULT
};


class GameManager
{
public:
	GameManager();
	~GameManager();

	bool FileInitialize();
	bool Initialize();
	int Update();
	void Draw2D();
	void Draw3D();

	static GameManager& Instance() {
		static GameManager instance;
		return instance;
	};

	SceneState GetSceneState() { return _scene_state; }
	void SetSceneState(SceneState scene_state) { _scene_state = scene_state; }

private:
	GameManager(const GameManager&) = delete;
	void operator=(const GameManager&) = delete;

	SceneManager* _scene_manager;

	SceneState _scene_state;
};