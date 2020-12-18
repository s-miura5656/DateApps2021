#include "MainScene.h"

#include "../../Managers/ItemManager/ItemManager.h"
#include "../../Managers/PlayerManager/PlayerManager.h"
#include "../../Managers/StageManager/StageManager.h"
#include "../../Managers/UIManager/UI.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"
#include "../../Managers/SceneManager/SceneManager.h"
#include "../../Managers/TimeManager/Time.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include "../../Data/IData.h"
#include "../../Data/Parametor.h"

MainScene::MainScene()
{
	_managers.push_back(new StageManager);
	_managers.push_back(new PlayerManager);
	//_managers.push_back(new ItemManager);
	_managers.push_back(new MainUiManager);
}

MainScene::~MainScene()
{
	ResouceManager::Instance().ResoucesEffekseerClear();

	for (int i = _managers.size() - 1; i >= 0; --i)
	{
		delete _managers[i];
	}
}

bool MainScene::Initialize()
{	
	/**
	* @brief ライトの初期設定
	*/
	Light light;
	light.Type = Light_Directional;
	light.Direction = Vector3(1, -1, 1);
	light.Diffuse = Color(1.0f, 1.0f, 1.0f);
	light.Ambient = Color(1.0f, 1.0f, 1.0f);
	light.Specular = Color(1.0f, 1.0f, 1.0f);

	SceneLight::Instance().SetLightParametor(light);
	SceneLight::Instance().SetSceneLight();

	auto view = GraphicsDevice.GetViewport();
	Vector3 camera_pos = Vector3(7, 11, -11.6);
	Vector3 look_pos = Vector3(65.2, 0, 0);
	//SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);
	SceneCamera::Instance().SetView(Vector3(7, 11, -11.6), Vector3(65.2, 0, 0));
	SceneCamera::Instance().SetPerspectiveFieldOfView(57, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	PlayerParametor::Instance().ResetParametor();
	ArmParametor::Instance().ResetParametor();

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

	float timeleft = TimeManager::Instance().GetTimeLeft();
	if (timeleft <= 0.9f)
	{
<<<<<<< HEAD
		ResultTransition();
=======
<<<<<<< HEAD
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
		SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::RESULT);

		delete pPlayerData;
=======
		ChangeSceneResult();
>>>>>>> cf893e710f413e5dde5084f45cb4a2ee7ff9259e
>>>>>>> fd01da56e21be856ceeb0274213800e37c991da6
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
}
<<<<<<< HEAD
void MainScene::ResultTransition()
=======
void MainScene::ChangeSceneResult()
>>>>>>> fd01da56e21be856ceeb0274213800e37c991da6
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
<<<<<<< HEAD
	SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::RESULT);

	delete pPlayerData;
=======
	SceneManager::Instance().ChangeScene(SceneManager::Instance().RESULT);
>>>>>>> fd01da56e21be856ceeb0274213800e37c991da6
}