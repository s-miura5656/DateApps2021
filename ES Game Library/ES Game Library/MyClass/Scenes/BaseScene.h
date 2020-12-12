//! @file   BaseScene.h
//! @brief  Scene—p‚ÌŠî’êƒNƒ‰ƒX
//! @author Souta_Miura
//! @date   2020/10/30

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
	virtual void DrawAlpha3D() = 0;
private:

};
