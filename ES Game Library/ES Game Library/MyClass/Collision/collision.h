#pragma once

#include "../../ESGLib.h"

class CollisionBase
{
private:


protected:
	MODEL hitbox;//���{
	Vector3 pos;
	//MODEL attack_box;//�U��
	//MODEL block_box;//�u���b�N
	//MODEL Stone_box;


public:
	CollisionBase();
	virtual ~CollisionBase();

	virtual void Initialize();
	virtual void Update();
	virtual void Draw3D();


};
