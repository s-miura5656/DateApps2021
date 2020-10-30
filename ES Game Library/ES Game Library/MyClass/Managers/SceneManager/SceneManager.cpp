#include "SceneManager.h"
#include "../../Scenes/Main/MainScene.h"

SceneManager::SceneManager()
{
	_main_scene = new MainScene;
}

SceneManager::~SceneManager()
{
	delete _main_scene;
}

bool SceneManager::FileInitialize()
{
	_main_scene->FileInitialize();

	return true;
}

bool SceneManager::Initialize()
{
	_main_scene->Initialize();

	return true;
}

int SceneManager::Update()
{
	_main_scene->Update();

	return 0;
}

void SceneManager::Draw2D()
{
	_main_scene->Draw2D();
}

void SceneManager::Draw3D()
{
	_main_scene->Draw3D();
}
