#pragma once

#include "../Itembase.hpp"

class AttackPowerItem : public ItemBase
{
public:
	AttackPowerItem(Vector3 position, std::string name);
	~AttackPowerItem();
	
	bool Initialize() override;
	void ItemEffect(std::string name) override { _iplayer_data->SetAttackPowor(name, _iplayer_data->GetAttackPowor(name) + _attack_powor); }
	int Update() override;

private:

};
