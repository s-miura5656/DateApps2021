#include "MainScene.h"
#include "../../Managers/ItemManager/ItemManager.h"
#include "../../Managers/PlayerManager/PlayerManager.h"
#include "../../Managers/StageManager/StageManager.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"

MainScene::MainScene()
{
	_managers.push_back(new StageManager);
	_managers.push_back(new PlayerManager);
	_managers.push_back(new ItemManager);
}

MainScene::~MainScene()
{
	for (int i = _managers.size() - 1; i >= 0; --i)
	{
		delete _managers[i];
	}
}

bool MainScene::Initialize()
{	
	/**
	* @brief �R���g���[���[�̎g�p�ő吔�ݒ�
	*/
	ControllerManager::Instance().SetGamePadMaxCount(PLAYER_COUNT_MAX);

	auto _temporary_managers = _managers;

	for (auto&& manager : _temporary_managers)
	{
		manager->Initialize();
	}

	return true;
}

int MainScene::Update()
{
	auto _temporary_managers = _managers;

	for (auto&& manager : _temporary_managers)
	{
		manager->Update();
	}

	return 0;
}

void MainScene::Draw2D()
{
	auto _temporary_managers = _managers;

	for (auto&& manager : _temporary_managers)
	{
		manager->Draw2D();
	}
}

void MainScene::Draw3D()
{
	auto _temporary_managers = _managers;

	for (auto&& manager : _temporary_managers)
	{
		manager->Draw3D();
	}
}
