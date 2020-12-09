#include "PlayerManager.h"
#include "../../Players/Player/Player.h"
#include "../../Data/WordsTable.h"

PlayerManager::PlayerManager()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);

		_players.push_back(new Player(tag));
	}

	_i_player_data = new IPrayerData;
}

PlayerManager::~PlayerManager()
{
	delete _i_player_data;

	for (int i = _players.size() - 1; i >= 0; --i)
	{
		delete _players[i];
	}
}

bool PlayerManager::Initialize()
{
	for (int i = 0; i < _players.size(); ++i)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);
		std::string arm_tag = ARM_TAG + std::to_string(i + 1);
		_players[i]->Initialize();

		PlayerParametor::Instance().CreateParametor(tag);

		ArmParametor::Instance().CreateParametor(arm_tag);

		_i_player_data->SetAngle(tag, 0);
	}

    return true;
}

int PlayerManager::Update()
{
	RankingSort();

	for (int i = 0; i < _players.size(); ++i)
	{
		_players[i]->Update();
	}

    return 0;
}

void PlayerManager::Draw2D()
{
	for (int i = 0; i < _players.size(); ++i)
	{
		_players[i]->Draw2D();
	}
}

void PlayerManager::Draw3D()
{
	for (int i = 0; i < _players.size(); ++i)
	{
		_players[i]->Draw3D();
	}
}

void PlayerManager::RankingSort()
{
	std::multimap<int, std::string, std::greater<int>> sorted_map;

	auto param_list = _i_player_data->GetAllParametor();

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);
		sorted_map.insert(std::make_pair(param_list[tag].ranking_point, tag));
	}
}

