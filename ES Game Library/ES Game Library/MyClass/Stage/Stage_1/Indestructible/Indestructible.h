/**
 * @file Indestructible.h
 * @brief ステージベースを継承した破壊できないステージブロック
 * @author 岩井瑞希
 * @date 2020/11/26
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"

class Indestructible :public StageBase
{
public:
	Indestructible();
	~Indestructible();
	bool Initialize() override;
	void Draw3D() override;
private:
};