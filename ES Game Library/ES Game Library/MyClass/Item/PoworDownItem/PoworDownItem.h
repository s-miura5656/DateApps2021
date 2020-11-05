#pragma once

#include "../Itembase.hpp"

class PoworDownItem : public ItemBase
{
public:
	PoworDownItem() {};
	~PoworDownItem() {};

	bool Initialize();
	int  Update();
	void Draw2D();
	void Draw3D();

private:

};
