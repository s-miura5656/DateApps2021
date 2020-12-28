#include "MainScene.h"

#include "../../Managers/ItemManager/ItemManager.h"
#include "../../Managers/PlayerManager/PlayerManager.h"
#include "../../Managers/StageManager/StageManager.h"
#include "../../Managers/UIManager/UI.h"
#include "../../Managers/SceneManager/SceneManager.h"
#include "../../Managers/TimeManager/Time.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include "../../Data/IData.h"
#include "../../Data/Parametor.h"
#include "../../Managers/InputManager/InputManager.h"

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
	camera_pos   = Vector3(7, 26.7f, -20.6f);
	camera_angle = Vector3(60.7, 0, 0);
	SceneCamera::Instance().SetView(camera_pos, camera_angle);
	SceneCamera::Instance().SetPerspectiveFieldOfView(25.3, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	PlayerParametor::Instance().ResetParametor();
	ArmParametor::Instance().ResetParametor();

	auto _temporary_managers = _managers;

	for (auto&& manager : _temporary_managers)
	{
		manager->Initialize();
	}

	InputDevice.CreateKeyboard();

	return true;
}

int MainScene::Update()
{
	auto _temporary_managers = _managers;

	for (auto&& manager : _temporary_managers)
	{
		manager->Update();
	}

	/*auto pad = InputManager::Instance().GetGamePad("Player_1");

	if (pad->Button(BUTTON_INFO::BUTTON_BACK))
	{
		camera_angle.x += 0.1f;
	}

	if (pad->Button(BUTTON_INFO::BUTTON_START))
	{
		camera_angle.x -=0.1f;
	}

	if (pad->Button(BUTTON_INFO::BUTTON_LEFT_SHOULDER))
	{
		camera_pos.z -= 0.1f;
	}

	if (pad->Button(BUTTON_INFO::BUTTON_RIGHT_SHOULDER))
	{
		camera_pos.z += 0.1f;
	}

	if (pad->Button(BUTTON_INFO::BUTTON_X))
	{
		camera_pos.y -= 0.1f;
	}

	if (pad->Button(BUTTON_INFO::BUTTON_Y))
	{
		camera_pos.y += 0.1f;
	}

	if (pad->Button(BUTTON_INFO::BUTTON_LEFT_THUMB))
	{
		parse -= 0.1f;
	}

	if (pad->Button(BUTTON_INFO::BUTTON_RIGHT_THUMB))
	{
		parse += 0.1f;
	}

	auto view = GraphicsDevice.GetViewport();*/

//	SceneCamera::Instance().SetView(camera_pos, camera_angle);
//	SceneCamera::Instance().SetPerspectiveFieldOfView(parse, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	float timeleft = TimeManager::Instance().GetTimeLeft();

	if (timeleft <= 0.9f)
	{
		ResultTransition();
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
void MainScene::ResultTransition()
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
	SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::RESULT);

	delete pPlayerData;
}

void MainScene::SetResoucesParticle()
{
	auto resouce = ResouceManager::Instance().LordEffekseerFile(_T("Effect/roket_punch/roket_punch_fixed.efk"));

	resouce = ResouceManager::Instance().LordEffekseerFile(_T("Effect/effekseer_hit/impossible_block.efk"));

	resouce = ResouceManager::Instance().LordEffekseerFile(_T("Effect/damage_effect01/damage_effect02.efk"));
}
