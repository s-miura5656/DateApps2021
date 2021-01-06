#pragma once

#include "Managers/ControllerManager/ContorollerManager.h"
#include "Data/IData.h"

class SelectScene : public BaseScene
{
public:
	SelectScene();
	~SelectScene();
	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override {}

private:

	EFFECT _shader;
	SPRITE _texture[PLAYER_COUNT_MAX];

	ANIMATIONMODEL _player_model;

	int _chara_select[PLAYER_COUNT_MAX];

	enum 
	{
		RED,
		BLUE,
		GREEN,
		YELLOW
	};
};