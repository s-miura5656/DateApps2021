#pragma once


#include "../../ESGLib.h"

class ItemBase {
public:
	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw2D();
	virtual void Draw3D();

protected:
	MODEL model;


private:




};