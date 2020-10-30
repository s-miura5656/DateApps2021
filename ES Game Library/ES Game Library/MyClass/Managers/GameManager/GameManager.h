#pragma once

#include "../../../ESGLib.h"

class SceneManager;

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

private:
	GameManager(const GameManager&) = delete;
	void operator=(const GameManager&) = delete;

	SceneManager* _scene_manager;
};