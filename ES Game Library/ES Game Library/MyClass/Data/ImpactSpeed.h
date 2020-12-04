#pragma once

#include"../../ESGLib.h"

class ImpactSpeed
{
public:

	bool Initialize(Vector3(attenuate));
	int Update(Vector3(impact_max), Vector3(attenuate_max));
	void impactSpeed(Vector3(attenuate_up), MODEL model);

private:

	Vector3 impact;
	Vector3 attenuate;

};