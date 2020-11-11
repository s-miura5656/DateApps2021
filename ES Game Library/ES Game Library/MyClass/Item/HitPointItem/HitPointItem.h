#pragma once


#include "../Itembase.hpp"

class HitPointItem : public ItemBase
{
public:
	HitPointItem(Vector3 position) { this->position = position; };
	~HitPointItem() {};

	bool Initialize();
	float itemEffect(float player_hit_point) { return player_hit_point + hit_point; }
	void Update();

private:

};
