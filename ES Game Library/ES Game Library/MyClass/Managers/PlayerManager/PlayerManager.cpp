#include "PlayerManager.h"
#include "../../Players/Player/Player.h"
#include "../../Data/GameData.h"

PlayerManager::PlayerManager()
{
	for (int i = 0; i < player_max_count; i++)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);
		std::string arm_name = ARM_TAG + std::to_string(i + 1);

		players.push_back(new Player(name, arm_name));
	}

	i_player_data = new IPrayerData;
}

PlayerManager::~PlayerManager()
{
	delete i_player_data;

	for (int i = players.size() - 1; i >= 0; --i)
	{
		delete players[i];
	}
}

bool PlayerManager::Initialize()
{
	//ゲームパッド
	//InputDevice.CreateGamePad(PLAYER_COUNT_MAX);

	Material player_mtrl[4];

	player_mtrl[0].Diffuse = Color(1.0f, 0.0f, 0.0f, 1.0f);
	player_mtrl[0].Ambient = Color(1.0f, 0.0f, 0.0f, 1.0f);
	player_mtrl[1].Diffuse = Color(0.0f, 1.0f, 0.0f, 0.3f);
	player_mtrl[1].Ambient = Color(0.0f, 1.0f, 0.0f, 0.3f);
	player_mtrl[2].Diffuse = Color(0.0f, 0.0f, 1.0f, 0.3f);
	player_mtrl[2].Ambient = Color(0.0f, 0.0f, 1.0f, 0.3f);
	player_mtrl[3].Diffuse = Color(1.0f, 1.0f, 0.0f, 0.3f);
	player_mtrl[3].Ambient = Color(1.0f, 1.0f, 0.0f, 0.3f);

	Vector3 _start_pos[4];

	_start_pos[0] = Vector3(-6.f, 0,  5.f);
	_start_pos[1] = Vector3( 6.f, 0,  5.f);
	_start_pos[2] = Vector3(-6.f, 0, -5.f);
	_start_pos[3] = Vector3( 6.f, 0, -5.f);

	LPCTSTR model_file_name = _T("player/robot.X");

//プレイヤー
	for (int i = 0; i < players.size(); ++i)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);
		std::string arm_name = ARM_TAG + std::to_string(i + 1);
		players[i]->FileInitialize(model_file_name);
		players[i]->PlayerColor(player_mtrl[i]);
		players[i]->SetContorollerNumber(i);
		players[i]->PlayerStartPosition(_start_pos[i]);
		players[i]->Initialize();

		ArmParametor::Instance().CreateParametor(ARM_TAG + std::to_string(i + 1));
		i_player_data->SetPosition(name, players[i]->GetPos());
		i_arm_data->SetPosition(arm_name, players[i]->GetPos());
	}

    return true;
}

int PlayerManager::Update()
{
	auto player = players;

	for (int i = 0; i < players.size(); ++i)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);
		std::string arm_name = ARM_TAG + std::to_string(i + 1);
		player[i]->Update();
		i_player_data->SetPosition(name, player[i]->GetPos());
		i_player_data->SetAngle(name, player[i]->GetAngle());
		i_arm_data->SetPosition(arm_name, players[i]->GetPos());
	}

    return 0;
}

void PlayerManager::Draw2D()
{
	auto player = players;

	for (int i = 0; i < players.size(); ++i)
	{
		player[i]->Draw2D();
	}
}

void PlayerManager::Draw3D()
{
	auto player = players;

	for (int i = 0; i < players.size(); ++i)
	{
		player[i]->Draw3D();
	}
}
