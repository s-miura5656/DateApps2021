#pragma once

#include"../../ESGLib.h"

class ImpactSpeed
{
public:
	ImpactSpeed();
	~ImpactSpeed();

	virtual bool Initialize(Vector3(impact_power), Vector3(attenuate_init));
	int Update(Vector3(attenuate_max));
	void impactSpeed(Vector3(attenuate_up), MODEL model);

private:

	Vector3 impact;
	Vector3 attenuate;

};