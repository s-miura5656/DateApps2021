#pragma once
#include "ArmBase.h"


class Arm :public ArmBase
{
public:
	Arm(std::string name);
	~Arm();

	bool Fileinitialize();
	bool Initialize();

	void ArmColor(Material& mat) {
		_model->SetMaterial(mat);
	}

private:
};
