#include "PlayerManager.h"
#include "../../Players/Player/Player.h"
#include "../../Data/WordsTable.h"
#include "../TimeManager/Time.h"

PlayerManager::PlayerManager()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);

		_players.push_back(new Player(tag));

		name[i] = PLAYER_TAG + std::to_string(i + 1);
	}

	_i_player_data = new IPrayerData;
	_crown_rotation = new CrownRotation;
}

PlayerManager::~PlayerManager()
{
	auto a = PlayerParametor::Instance()._player_params;

	PlayerParametor::Instance().ResetParametor();
	ArmParametor::Instance().ResetParametor();

	delete _crown_rotation;	_crown_rotation = nullptr;
	delete _i_player_data;	_i_player_data  = nullptr;

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
	}

	
	_crown_rotation->Initialize();
	
    return true;
}

int PlayerManager::Update()
{
	if (TimeManager::Instance().StartFlag())
	{
		RankingSort();

		for (int i = 0; i < _players.size(); ++i)
		{
			_players[i]->Update();
		}

		_crown_rotation->Update();
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
	_crown_rotation->Draw3D();
}

void PlayerManager::DrawAlpha3D()
{
	for (int i = 0; i < _players.size(); ++i)
	{
		_players[i]->DrawAlpha3D();
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


	for (auto it = sorted_map.begin(); it != sorted_map.end(); ++it)
	{
		auto num = distance(sorted_map.begin(), it);

		_i_player_data->SetRankNum((*it).second, num);
	}

	return;
}

