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

<<<<<<< HEAD
	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override;
=======
	bool Initialize();
	int Update();
	void Draw2D();
	void Draw3D();
	void ChangeSceneResult();
>>>>>>> cf893e710f413e5dde5084f45cb4a2ee7ff9259e
private:

	std::vector<ManagerBase*> _managers;
};