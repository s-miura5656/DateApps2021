#pragma once
#include "ArmBase.h"


class Arm :public ArmBase
{
public:
	Arm(std::string name, std::string arm_name);
	~Arm();

	bool Fileinitialize();
	bool Initialize();

	void ArmColor(Material& mat) {
		arm_model->SetMaterial(mat);
	}

private:
	
	
	
	
};
