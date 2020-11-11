#pragma once

#include "../../ESGLib.h"

class ItemBase
{
public:
	ItemBase() {};
	virtual ~ItemBase() {}
	virtual bool Initialize();
	virtual void Update();
	virtual void Draw2D();
	virtual void Draw3D();
	virtual float itemEffect(float num) { return num; }
	void SphereShape();
		

protected:
	float hit_point = 1000.f;
	float attack_powor = 100.f;
	float speed = 50.f;

	MODEL sphere;
	Vector3 position;

private:
	
};