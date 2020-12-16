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
		ChangeSceneResult();
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

	Effekseer.Draw();
}
void MainScene::ChangeSceneResult()
{
	// ここでプレイヤーマネージャーから各プレイヤーのポイントを取得
	int points[PLAYER_COUNT_MAX] = {};
	int ranknum[PLAYER_COUNT_MAX] = {};
	IPrayerData* pPlayerData = new IPrayerData;
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);
		points[i] = pPlayerData->GetRankingPoint(tag);
		ranknum[i] = i + 1;
	}
	int temp;
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		for (int j = PLAYER_COUNT_MAX - 1; j > i; j--)
		{
			if (points[j - 1] < points[j])
			{
				temp = points[j - 1];
				points[j - 1] = points[j];
				points[j] = temp;
				temp = ranknum[j - 1];
				ranknum[j - 1] = ranknum[j];
				ranknum[j] = temp;
			}
		}
	}
	SceneManager::Instance().SetResultData(ranknum, points);//プレイヤー名とポイント数を一位から昇順に並べ、代入する。
	SceneManager::Instance().ChangeScene(SceneManager::Instance().RESULT);
}