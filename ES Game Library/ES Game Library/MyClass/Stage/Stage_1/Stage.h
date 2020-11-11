#pragma once

#include "../StageBase.h"
#include"../../Stage/Stage_1/Block/Block.h"

class Stage : public StageBase
{
public:
	bool Initialize() override;
	//void Draw3D() override;
private:
	Vector3 map_position;
	Block* block;
};