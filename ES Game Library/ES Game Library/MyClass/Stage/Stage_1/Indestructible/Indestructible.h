/**
 * @file Indestructible.h
 * @brief ステージベースを継承した破壊できないステージブロック
 * @author 岩井瑞希
 * @date 2020/11/26
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"
#include "../../../Data/IData.h"
class Indestructible :public StageBase
{
public:
	Indestructible(std::string tag);
	~Indestructible();
	bool Initialize() override;
	int Update() override;
	void Draw3D() override;
private:
	std::unique_ptr<IArmData>		_i_arm_data;
	float                           _speed = 0.05;
	bool                            _move_flag = false;
};