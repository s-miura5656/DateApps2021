#pragma once

#include "../../ESGLib.h"
#include "../Data/IData.h"

class BaseUi {
public:
	BaseUi() {}
	virtual ~BaseUi() {}

	virtual bool Initialize() = 0;
	virtual int Update() = 0;
	virtual void Draw2D() = 0;
private:
};