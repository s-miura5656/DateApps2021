#pragma once

#include "../../ESGLib.h"
#include "../Collision/HitBox.h"
#include "../Data/IPlayerData.h"

class ItemBase
{
public:
	ItemBase() {};
	virtual ~ItemBase() {}
	virtual bool Initialize();
	virtual int Update();
	virtual void Draw2D();
	virtual void Draw3D();
	virtual void ItemEffect(std::string name) { name; }
	void SphereShape();
		

protected:
	int _hit_point    = 1000;
	int _attack_powor = 100;
	int _speed		  = 50;

	MODEL _sphere;
	Vector3 _position;
	IPrayerData* _iplayer_data;
	std::unique_ptr<HitBox> _hit_box;
private:
	
};