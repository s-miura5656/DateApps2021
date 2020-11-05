#pragma once

#include "../../ESGLib.h"

class CollisionBase
{
private:


protected:
	MODEL hitbox;//ロボ
	Vector3 pos;
	//MODEL attack_box;//攻撃
	//MODEL block_box;//ブロック
	//MODEL Stone_box;


public:
	CollisionBase();
	virtual ~CollisionBase();

	virtual void Initialize();
	virtual void Update();
	virtual void Draw3D();


};
