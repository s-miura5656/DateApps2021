#include "SceneManager.h"
#include "../../Scenes/Main/MainScene.h"
#include "../GameManager/GameManager.h"

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
	auto scene = GameManager::Instance().GetSceneState();

	switch (scene)
	{
	case SceneState::TITLE:
		break;
	case SceneState::MAIN:
		_main_scene->FileInitialize();
		break;
	case SceneState::RESULT:
		break;
	}


	return true;
}

bool SceneManager::Initialize()
{
	auto scene = GameManager::Instance().GetSceneState();

	switch (scene)
	{
	case SceneState::TITLE:
		break;
	case SceneState::MAIN:
		_main_scene->Initialize();
		break;
	case SceneState::RESULT:
		break;
	}


	return true;
}

int SceneManager::Update()
{
	auto scene = GameManager::Instance().GetSceneState();

	switch (scene)
	{
	case SceneState::TITLE:
		break;
	case SceneState::MAIN:
		_main_scene->Update();
		break;
	case SceneState::RESULT:
		break;
	}


	return 0;
}

void SceneManager::Draw2D()
{
	auto scene = GameManager::Instance().GetSceneState();

	switch (scene)
	{
	case SceneState::TITLE:
		break;
	case SceneState::MAIN:
		_main_scene->Draw2D();
		break;
	case SceneState::RESULT:
		break;
	}

}

void SceneManager::Draw3D()
{
	auto scene = GameManager::Instance().GetSceneState();

	switch (scene)
	{
	case SceneState::TITLE:
		break;
	case SceneState::MAIN:
		_main_scene->Draw3D();
		break;
	case SceneState::RESULT:
		break;
	}

}
