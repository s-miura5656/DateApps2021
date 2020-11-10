#pragma once


#include "../ItemBase.hpp"

class AttackPowerItem : public ItemBase
{
public:
	AttackPowerItem() {};
	~AttackPowerItem() {};

	bool Initialize();
	float itemEffect(float player_attack_powor) { return player_attack_powor + attack_powor; }
	void Update();
	void Draw2D();
	void Draw3D();

private:

};
