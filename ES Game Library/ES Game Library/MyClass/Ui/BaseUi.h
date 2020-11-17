#pragma once

#include "../../ESGLib.h"
#include "../Data/IPlayerData.h"

class PlayerBase;

class BaseUi {
public:
	BaseUi() {}
	virtual ~BaseUi() {}

	virtual bool Initialize() = 0;
	virtual int Update() = 0;
	virtual void Draw2D() = 0;
#ifdef _DEBUG
	virtual void DebugDraw(PlayerBase* player) {}
#endif

protected:
	FONT time_limit_font;
	IPrayerData* iplayer_data;

private:
};