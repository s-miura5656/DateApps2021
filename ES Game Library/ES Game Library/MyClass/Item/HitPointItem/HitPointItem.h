#pragma once


#include "../Itembase.hpp"

class HitPointItem : public ItemBase
{
public:
	HitPointItem(Vector3 position, std::string name);
	~HitPointItem();

	bool Initialize() override;
	void ItemEffect(std::string name) override { _iplayer_data->SetHitPoint(name, _iplayer_data->GetHitPoint(name) + _hit_point); }
	int Update() override;

private:

};
