#include "PlayerManager.h"
#include "../../Players/Player/Player.h"
#include "../../Data/WordsTable.h"
#include "../TimeManager/Time.h"
#include "../../Players/TypeSetting/TypeSetting.h"

PlayerManager::PlayerManager()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);

		_players.push_back(std::make_unique<Player>(tag));

		name[i] = PLAYER_TAG + std::to_string(i + 1);
	}
	              
	_i_player_data.reset(new IPrayerData);
	_crown_rotation.reset(new CrownRotation);
}

PlayerManager::~PlayerManager()
{
	_crown_rotation.reset();	
	_i_player_data.reset();

	for (int i = _players.size() - 1; i >= 0; --i)
	{
		_players[i].reset();
	}
}

bool PlayerManager::Initialize()
{
	TypeSetting::Instance().Initialize();

	for (int i = 0; i < PLAYER_COUNT_MAX; i += 2)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);
		std::string arm_tag = ARM_TAG + std::to_string(i + 1);
		InitializeCharactorParametor(tag, arm_tag, i + 1);

		tag = PLAYER_TAG + std::to_string(i + 2);
		arm_tag = ARM_TAG + std::to_string(i + 2);
		InitializeCharactorParametor(tag, arm_tag, i + 2);
	}

	for (int i = 0; i < _players.size(); ++i)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);
		_players[i]->Initialize();
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

void PlayerManager::InitializeCharactorParametor(std::string player_tag, std::string arm_tag, int type)
{
	PlayerParametor::Instance().CreateParametor(player_tag);
	ArmParametor::Instance().CreateParametor(arm_tag);

	//! これはキャラクター選択に追加する
	TypeSetting::Instance().SetPlayerType(player_tag, type);
	
	auto charactor_param = TypeSetting::Instance().GetCharactorParam(TypeSetting::Instance().GetPlayerType(player_tag));

	charactor_param.player_param.position = _i_player_data->GetPosition(player_tag);

	_i_player_data->SetParametor(player_tag, charactor_param.player_param);
	_i_arm_data->SetArmParam(arm_tag, charactor_param.arm_param);
}

