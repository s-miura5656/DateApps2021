#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"
#include"../../../Data/WordsTable.h"
class WallCorner :public StageBase
{
public:
	WallCorner();
	~WallCorner();
	bool Initialize() override;
private:
};