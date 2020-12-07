#pragma once

#include "../../ESGLib.h"
#include "../EffectBase.h"
#include "../Data/WordsTable.h"
#include "../Data/IData.h"

class EffectManager
{
public:
	EffectManager();
	~EffectManager();
	
	bool Initialize();
	void Update();
	void Draw();

private:
	EffectBase eb[EffectEnum::ALL_TYPE];
	string player_tag;
	IPrayerData player_data;
	bool flag = true;
};
