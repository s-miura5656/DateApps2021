#pragma once

#include "../../ESGLib.h"

class BaseScene
{
public:
	BaseScene() {};
	virtual ~BaseScene() {};

	virtual bool Initialize() = 0;
	virtual int Update() = 0;
	virtual void Draw2D() = 0;
	virtual void Draw3D() = 0;

private:

};
