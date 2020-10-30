#include "GameManager.h"
#include "../SceneManager/SceneManager.h"

GameManager::GameManager()
{
	_scene_manager = new SceneManager;
}

GameManager::~GameManager()
{
	delete _scene_manager;
}

bool GameManager::FileInitialize()
{
	_scene_manager->FileInitialize();

	return false;
}

bool GameManager::Initialize()
{
	_scene_manager->Initialize();

	return false;
}

int GameManager::Update()
{
	_scene_manager->Update();

	return 0;
}

void GameManager::Draw2D()
{
	_scene_manager->Draw2D();
}

void GameManager::Draw3D()
{
	_scene_manager->Draw3D();
}