//! @file   MainScene.h
//! @brief  MainScene�𓮂����ׂ̃N���X
//! @author Souta_Miura
//! @date   2020/10/30
#pragma once

#include "../BaseScene.h"
#include "../../Managers/ManagerBase.h"
#include"../../Players/Crown/CrownRotation.h"

class MainScene : public BaseScene
{
public:
	MainScene();
	~MainScene();

	bool Initialize();
	int Update();
	void Draw2D();
	void Draw3D();

private:

	std::vector<ManagerBase*> _managers;

	CrownRotation crownrotation;
};