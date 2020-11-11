#pragma once


#include "../Itembase.hpp"

class HitPointItem : public ItemBase
{
public:
	HitPointItem(Vector3 position) { this->_position = position; };
	~HitPointItem() {};

	bool Initialize();
	float itemEffect(float player_hit_point) { return player_hit_point + _hit_point; }
	bool Update();

private:

};
