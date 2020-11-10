#include "PlayerManager.h"

#include "../../Players/Player/Player.h"

PlayerManager::PlayerManager()
{
	for (int i = 0; i < player_max_count; i++)
	{
		name.push_back("Player_" + std::to_string(i + 1));
		players.push_back(new Player(name[i]));
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
	InputDevice.CreateGamePad(PLAYER_MAX);

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

	LPCTSTR model_file_name = _T("player/robot_02.X");

	//プレイヤー
	for (int i = 0; i < players.size(); ++i)
	{
		players[i]->FileInitialize(model_file_name);
		players[i]->PlayerColor(player_mtrl[i]);
		players[i]->SetContorollerNumber(i);
		players[i]->PlayerStartPosition(_start_pos[i]);
		players[i]->Initialize();
		i_player_data->SetPosition(name[i], players[i]->PlayerGetPos());
	}

    return true;
}

int PlayerManager::Update()
{
	auto player = players;

	for (int i = 0; i < players.size(); ++i)
	{
		player[i]->Update();
		i_player_data->SetPosition(name[i], player[i]->PlayerGetPos());
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
