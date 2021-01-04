#pragma once

#include "../Itembase.hpp"
#include"../../Data/IData.h"

class PointItem : public ItemBase
{
public:
	PointItem(Vector3 position, std::string name, int point);
	~PointItem();

	bool Initialize() override;
	int Update() override;

private:
	float _rotation;
	int _point;
};