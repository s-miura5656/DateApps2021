#pragma once


#include "../Itembase.hpp"

class AttackPowerItem : public ItemBase
{
public:
	AttackPowerItem(Vector3 position) { this->position = position; };
	~AttackPowerItem() {};

	bool Initialize();
	float itemEffect(float player_attack_powor) { return player_attack_powor + attack_powor; }
	void Update();

private:

};
