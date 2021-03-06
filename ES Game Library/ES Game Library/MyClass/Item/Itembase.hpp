#pragma once

#include "../../ESGLib.h"
#include "../Collision/HitBox.h"
#include "../Data/IData.h"

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
	void BoxShape();
	void RotationItem();
	bool IsFlag() const { return Removeflag; };

protected:
	int _hit_point    = 1000;
	int _attack_powor = 100;
	float _speed		  = 0.01f;

	MODEL _box;
	Vector3 _position;
	IPrayerData* _i_player_data;
	std::unique_ptr<HitBox> _hit_box;

	bool Removeflag = false;
	float _rotation = 0.f;
private:
	
};