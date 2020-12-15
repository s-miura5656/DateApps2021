#include "MainScene.h"

#include "../../Managers/ItemManager/ItemManager.h"
#include "../../Managers/PlayerManager/PlayerManager.h"
#include "../../Managers/StageManager/StageManager.h"
#include "../../Managers/UIManager/UI.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"
#include "../../Managers/SceneManager/SceneManager.h"
#include"../../Managers/TimeManager/Time.h"
MainScene::MainScene()
{
	_managers.push_back(new StageManager);
	_managers.push_back(new PlayerManager);
	_managers.push_back(new ItemManager);
	_managers.push_back(new MainUiManager);
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
	auto _temporary_managers = _managers;

	Effekseer.Attach(GraphicsDevice);

	for (auto&& manager : _temporary_managers)
	{
		manager->Initialize();
	}

	Effekseer.SetCamera(SceneCamera::Instance().GetCamera());

	ControllerManager::Instance().SetGamePadMaxCount(PLAYER_COUNT_MAX);

	return true;
}

int MainScene::Update()
{
	auto _temporary_managers = _managers;

	Effekseer.Update();

	for (auto&& manager : _temporary_managers)
	{
		manager->Update();
	}

	float timeleft = TimeManager::Instance().GetTimeLeft();
	if (timeleft <= 0.9f)
	{
		// �����Ńv���C���[�}�l�[�W���[����e�v���C���[�̃|�C���g���擾
		int points[PLAYER_COUNT_MAX] = {};

		// �|�C���g���r����1�ʂ𔻒�
		// GetRankNum()�����Ĉ�ʂ̃v���C���[���擾
		std::vector<std::string> playerTable;
		playerTable.push_back(PLAYER_TAG + "1");
		playerTable.push_back(PLAYER_TAG + "2");
		playerTable.push_back(PLAYER_TAG + "3");
		playerTable.push_back(PLAYER_TAG + "4");

		std::string winner;
		IPrayerData* pPlayerData = new IPrayerData;
		for (auto&& tag : playerTable)
		{
			if ((pPlayerData->GetRankNum(tag) + 1) == 1)
			{
				winner = tag;
				break;
			}
		}
		for (int i = 0; i < PLAYER_COUNT_MAX; i++)
		{
			std::string tag = PLAYER_TAG + std::to_string(i + 1);
			points[i] = pPlayerData->GetRankingPoint(tag);
		}
		SceneManager::Instance().SetResultData(winner, points);	// �����ŒN����ʂ���������Player�^�O�Ŕ��肷�邽�߁A����1��string,����2��int�̃|�C���^		
		SceneManager::Instance().ChangeScene(SceneManager::Instance().RESULT);
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

void MainScene::DrawAlpha3D()
{
	auto _temporary_managers = _managers;

	for (auto&& manager : _temporary_managers)
	{
		manager->DrawAlpha3D();
	}

	Effekseer.Draw();
}
