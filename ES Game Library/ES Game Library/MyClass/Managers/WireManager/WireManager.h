#pragma once 

#include "../../../ESGLib.h"
#include "../ManagerBase.h"
#include "../../Data/StructList.h"

class WireManager : public ManagerBase
{
public:
	WireManager();
	~WireManager();

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;

private:
	
};