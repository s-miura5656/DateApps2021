#pragma once

#include "../../../ESGLib.h"

class ResultScene {
public:
	bool FileInitialize();
	bool Initialize();
	int Update();
	void Draw2D();
	void Draw3D();
private:
	SPRITE result;
};