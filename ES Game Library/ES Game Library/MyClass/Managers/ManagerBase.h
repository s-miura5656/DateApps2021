//! @file   ManagerBase.h
//! @brief  マネージャー用の基底クラス
//! @author Souta_Miura
//! @date   2020/11/05
#pragma once

#include "../../ESGLib.h"

class ManagerBase
{
public:
	ManagerBase() {};
	virtual ~ManagerBase() {};

	virtual bool Initialize() = 0;
	virtual int Update() = 0;
	virtual void Draw2D() = 0;
	virtual void Draw3D() = 0;

private:

};

