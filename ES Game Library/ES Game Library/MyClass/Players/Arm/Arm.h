#pragma once
#include "ArmBase.h"


class Arm :public ArmBase
{
public:
	Arm(std::string name);
	~Arm();

	bool Initialize() override;

private:
};
