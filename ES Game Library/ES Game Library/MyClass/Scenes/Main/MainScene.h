//! @file   MainScene.h
//! @brief  MainScene‚ð“®‚©‚·ˆ×‚ÌƒNƒ‰ƒX
//! @author Souta_Miura
//! @date   2020/10/30
#pragma once

#include "../BaseScene.h"
#include "../../Managers/ManagerBase.h"

class MainScene : public BaseScene
{
public:
	MainScene();
	~MainScene();

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override;
private:
	void ResultTransition();
	void SetResoucesParticle();
	std::vector<ManagerBase*> _managers;

	Vector3 camera_pos = Vector3(7, 16, -12.0f);
	Vector3 camera_angle = Vector3(60, 0, 0);
	float parse = 40;
};