#pragma once

#include "../Itembase.hpp"

class SpeedItem : public ItemBase
{
public:
	SpeedItem(Vector3 position, std::string name);
	~SpeedItem();

	bool Initialize() override;
	void ItemEffect(std::string name) override { _i_player_data->SetSpeed(name, _i_player_data->GetSpeed(name) + _speed); }
	int Update() override;

private:
	float _rotation;
};