#pragma once


#include "../ItemBase.hpp"

class HitPointItem : public ItemBase
{
public:
	HitPointItem() {};
	~HitPointItem() {};

	bool Initialize();
	float itemEffect(float player_hit_point) { return player_hit_point + hit_point; }
	void Update();
	void Draw2D();
	void Draw3D();

private:

};
