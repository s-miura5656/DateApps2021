#pragma once
#include "ArmBase.h"


class Arm :public ArmBase
{
public:
	Arm();
	~Arm();

	bool Fileinitialize();
	bool Initialize();
	int  Update(Vector3 player_pos, float player_angle);

	void ArmShoot(int flag);

	void ArmColor(Material& mat) {
		arm_model->SetMaterial(mat);
	}

	void SetPra(Vector3 pos, float angle);

	int GetArmState() { return arm_state; }

private:
	
	Vector3 arm_get_pos;
	Vector3 arm_get_rot;

	Vector3 player_get_pos;
	float player_get_angle;
	
	
};
