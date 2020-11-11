#pragma once


#include "../Itembase.hpp"

class SpeedItem : public ItemBase
{
public:
	SpeedItem(Vector3 position) { this->_position = position; };
	~SpeedItem() {};

	bool Initialize();
	float itemEffect(float player_speed) { return player_speed + _speed; }
	bool Update();


private:

};