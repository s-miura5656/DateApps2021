//! @file   MainScene.h
//! @brief  MainSceneを動かす為のクラス
//! @author Souta_Miura
//! @date   2020/10/30

#pragma once

#include "../BaseScene.h"

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

};