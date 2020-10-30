#pragma once

#include "../../../ESGLib.h"

class TitleScene {
public:
	bool FileInitialize();
	bool Initialize();
	int Update();
	void Draw2D();
	void Draw3D();
private:
	SPRITE _title;
};