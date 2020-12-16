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
		// ここでプレイヤーマネージャーから各プレイヤーのポイントを取得
		int points[PLAYER_COUNT_MAX] = {};
		int ranknum[PLAYER_COUNT_MAX] = {};
		IPrayerData* pPlayerData = new IPrayerData;
		for (int i = 0; i < PLAYER_COUNT_MAX; i++)
		{
			std::string tag = PLAYER_TAG + std::to_string(i + 1);
			if (pPlayerData->GetRankNum(tag) == 0) {
				points[0] = pPlayerData->GetRankingPoint(tag);
				ranknum[0] = i + 1;
				break;
			}
		}
		for (int i = 0; i < PLAYER_COUNT_MAX; i++)
		{
			std::string tag = PLAYER_TAG + std::to_string(i + 1);
			if (pPlayerData->GetRankNum(tag) == 1) {
				points[1] = pPlayerData->GetRankingPoint(tag);
				ranknum[1] = i + 1;
				break;
			}
		}
		for (int i = 0; i < PLAYER_COUNT_MAX; i++)
		{
			std::string tag = PLAYER_TAG + std::to_string(i + 1);
			if (pPlayerData->GetRankNum(tag) == 2) {
				points[2] = pPlayerData->GetRankingPoint(tag);
				ranknum[2] = i + 1;
				break;
			}
		}
		for (int i = 0; i < PLAYER_COUNT_MAX; i++)
		{
			std::string tag = PLAYER_TAG + std::to_string(i + 1);
			if (pPlayerData->GetRankNum(tag) == 3) {
				points[3] = pPlayerData->GetRankingPoint(tag);
				ranknum[3] = i + 1;
				break;
			}
		}
		SceneManager::Instance().SetResultData(ranknum, points);	// ここで誰が一位だったかをPlayerタグで判定するため、引数1はstring,引数2はintのポインタ		
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

	Effekseer.Draw();
}
