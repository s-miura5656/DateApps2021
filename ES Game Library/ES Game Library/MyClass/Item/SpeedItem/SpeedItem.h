#pragma once

#include "../Itembase.hpp"

class SpeedItem : public ItemBase
{
public:
	SpeedItem(Vector3 position, std::string name);
	~SpeedItem();

	bool Initialize() override;
	void ItemEffect(std::string name) override { _iplayer_data->SetSpeed(name, _iplayer_data->GetSpeed(name) + _speed); }
	int Update() override;

private:
	float _rotation;
};