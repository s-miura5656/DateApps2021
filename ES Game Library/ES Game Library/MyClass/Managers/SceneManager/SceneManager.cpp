#include "SceneManager.h"
#include "../../Scenes/Main/MainScene.h"
#include "../GameManager/GameManager.h"
#include "../../Scenes/Title/TitleScene.h"
#include"../../Scenes/Result/ResultScene.h"
SceneManager::SceneManager()
{
	_title_scene = new TitleScene;
	_main_scene = new MainScene;
	_result_scene = new ResultScene;
}

SceneManager::~SceneManager()
{
	delete _result_scene;
	delete _main_scene;
	delete _title_scene;
}

bool SceneManager::FileInitialize()
{
	auto scene = GameManager::Instance().GetSceneState();

	switch (scene)
	{
	case SceneState::TITLE:
		_title_scene->FileInitialize();
		break;
	case SceneState::MAIN:
		_main_scene->FileInitialize();
		break;
	case SceneState::RESULT:
		_result_scene->FileInitialize();
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
		_title_scene->Initialize();
		break;
	case SceneState::MAIN:
		_main_scene->Initialize();
		break;
	case SceneState::RESULT:
		_result_scene->Initialize();
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
		_title_scene->Update();
		break;
	case SceneState::MAIN:
		_main_scene->Update();
		break;
	case SceneState::RESULT:
		_result_scene->Update();
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
		_title_scene->Draw2D();
		break;
	case SceneState::MAIN:
		_main_scene->Draw2D();
		break;
	case SceneState::RESULT:
		_result_scene->Draw2D();
		break;
	}

}

void SceneManager::Draw3D()
{
	auto scene = GameManager::Instance().GetSceneState();

	switch (scene)
	{
	case SceneState::TITLE:
		_title_scene->Draw3D();
		break;
	case SceneState::MAIN:
		_main_scene->Draw3D();
		break;
	case SceneState::RESULT:
		_result_scene->Draw3D();
		break;
	}

}
