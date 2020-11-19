#include "PlayerManager.h"
#include "../../Players/Player/Player.h"
#include "../../Data/WordsTable.h"

PlayerManager::PlayerManager()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		players.push_back(new Player(name));
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
	Material player_mtrl[PLAYER_COUNT_MAX];

	player_mtrl[0].Diffuse = Color(1.0f, 0.0f, 0.0f, 1.0f);
	player_mtrl[0].Ambient = Color(1.0f, 0.0f, 0.0f, 1.0f);
	player_mtrl[1].Diffuse = Color(0.0f, 1.0f, 0.0f, 0.3f);
	player_mtrl[1].Ambient = Color(0.0f, 1.0f, 0.0f, 0.3f);
	player_mtrl[2].Diffuse = Color(0.0f, 0.0f, 1.0f, 0.3f);
	player_mtrl[2].Ambient = Color(0.0f, 0.0f, 1.0f, 0.3f);
	player_mtrl[3].Diffuse = Color(1.0f, 1.0f, 0.0f, 0.3f);
	player_mtrl[3].Ambient = Color(1.0f, 1.0f, 0.0f, 0.3f);

	LPCTSTR model_file_name = _T("player/robot.X");

//ÉvÉåÉCÉÑÅ[
	for (int i = 0; i < players.size(); ++i)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);
		std::string arm_name = ARM_TAG + std::to_string(i + 1);
		players[i]->FileInitialize(model_file_name);
		players[i]->PlayerColor(player_mtrl[i]);
		players[i]->Initialize();

		ArmParametor::Instance().CreateParametor(ARM_TAG + std::to_string(i + 1));
		i_player_data->SetPosition(name, players[i]->GetPos());
		i_arm_data->SetPosition(arm_name, players[i]->GetPos());
	}

    return true;
}

int PlayerManager::Update()
{
	for (int i = 0; i < players.size(); ++i)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);
		std::string arm_name = ARM_TAG + std::to_string(i + 1);
		players[i]->Update();
		i_player_data->SetPosition(name, players[i]->GetPos());
		i_player_data->SetAngle(name, players[i]->GetAngle());
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
