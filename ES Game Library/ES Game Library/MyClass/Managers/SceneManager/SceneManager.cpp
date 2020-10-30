#include "SceneManager.h"
#include "../../Scenes/Main/MainScene.h"
#include "../../Scenes/Title/TitleScene.h"
#include"../../Scenes/Result/ResultScene.h"

SceneManager::SceneManager()
{
	//! ˆê”ÔÅ‰‚É“Ç‚Ýž‚Ü‚ê‚éƒV[ƒ“
	ChangeScene(SceneState::TITLE);
}

SceneManager::~SceneManager()
{
	delete _scene;
	delete _result_scene;
	delete _main_scene;
	delete _title_scene;
}

void SceneManager::ChangeScene(SceneState scene)
{
	if (_scene != nullptr) 
		delete _scene;
	
	switch (scene) {
	case SceneState::TITLE:
		_scene = new TitleScene;
		break;
	case SceneState::MAIN:
		_scene = new MainScene;
		break;
	case SceneState::RESULT:
		_scene = new ResultScene;
		break;
	}

	_scene->Initialize();
}

bool SceneManager::Initialize()
{
	

	return true;
}

int SceneManager::Update()
{
	

	return 0;
}

void SceneManager::Draw2D()
{
	

}

void SceneManager::Draw3D()
{
	

}


