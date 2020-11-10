#pragma once

#include "../StageBase.h"

class Stage : public StageBase
{
public:
	bool Initialize() override;
	void Draw3D() override;
private:
	Vector3 map_position;
	Material material;
};