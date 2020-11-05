#pragma once

#include "../Itembase.hpp"

class PoworUpItem : public ItemBase 
{
public:
	PoworUpItem() {};
	~PoworUpItem() {};

	bool Initialize();
	int  Update();
	void Draw2D();
	void Draw3D();

private:

};
