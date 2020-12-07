#pragma once

#include "../../../ESGLib.h"
#include "EffectBase.h"
#include "../../Data/WordsTable.h"
#include "../../Data/IData.h"
#include "../../Managers/ManagerBase.h"

class EffectManager : public ManagerBase
{
public:
	EffectManager();
	~EffectManager();
	
	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;

private:
	EffectBase eb[EffectEnum::ALL_TYPE];
	string player_tag;
	IPrayerData _i_player_data;
	bool flag = true;
};
