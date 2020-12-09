#include "PlayerManager.h"
#include "../../Players/Player/Player.h"
#include "../../Data/WordsTable.h"

PlayerManager::PlayerManager()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);

		players.push_back(new Player(tag));
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
	for (int i = 0; i < players.size(); ++i)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);
		std::string arm_tag = ARM_TAG + std::to_string(i + 1);
		players[i]->Initialize();

		PlayerParametor::Instance().CreateParametor(tag);
		ArmParametor::Instance().CreateParametor(arm_tag);
	}

	crownrotation.Initialize();
	
    return true;
}

int PlayerManager::Update()
{
	RankingSort();

	for (int i = 0; i < players.size(); ++i)
	{
		players[i]->Update();
	}

	crownrotation.Update();

    return 0;
}

void PlayerManager::Draw2D()
{
	for (int i = 0; i < players.size(); ++i)
	{
		players[i]->Draw2D();
	}
}

void PlayerManager::Draw3D()
{
	for (int i = 0; i < players.size(); ++i)
	{
		players[i]->Draw3D();
	}

	crownrotation.Draw3D();
}

void PlayerManager::RankingSort()
{
	std::multimap<int, std::string, std::greater<int>> sorted_map;
	auto param_list = i_player_data->GetAllParametor();

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);
		sorted_map.insert(std::make_pair(param_list[tag].kill_count, tag));
	}
}

