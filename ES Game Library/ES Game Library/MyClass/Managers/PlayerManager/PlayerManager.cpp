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
	LPCTSTR model_file_name = _T("player/robot.X");

	//ÉvÉåÉCÉÑÅ[
	for (int i = 0; i < players.size(); ++i)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);
		std::string arm_name = ARM_TAG + std::to_string(i + 1);
		players[i]->Initialize();

		PlayerParametor::Instance().CreateParametor(name);
		ArmParametor::Instance().CreateParametor(arm_name);
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
		/*i_player_data->setposition(name, players[i]->getpos());
		i_player_data->setangle(name, players[i]->getangle());*/
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
