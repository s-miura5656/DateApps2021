#pragma once


#include "../Itembase.hpp"

class HitPointItem : public ItemBase
{
public:
	HitPointItem(Vector3 position, std::string name);
	~HitPointItem();

	bool Initialize() override;
	void ItemEffect(std::string name) override { _i_player_data->SetHitPoint(name, _i_player_data->GetHitPoint(name) + _hit_point); }
	int  Update() override;

private:
	float _rotation;
};
