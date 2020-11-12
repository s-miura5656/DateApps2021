#pragma once


#include "../ItemBase.hpp"

class SpeedItem : public ItemBase
{
public:
	SpeedItem() {};
	~SpeedItem() {};

	bool Initialize();
	float itemEffect(float player_speed) { return player_speed + speed; }
	void Update();
	void Draw2D();
	void Draw3D();



private:

};