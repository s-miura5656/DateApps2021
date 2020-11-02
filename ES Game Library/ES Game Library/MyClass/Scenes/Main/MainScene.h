//! @file   MainScene.h
//! @brief  MainScene�𓮂����ׂ̃N���X
//! @author Souta_Miura
//! @date   2020/10/30

#pragma once

#include "../BaseScene.h"
#include "../../Player/PlayerBase.h"

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

	CAMERA camera;

	//�v���C���[
	PlayerBase player1;
	PlayerBase player2;
	PlayerBase player3;
	PlayerBase player4;

};