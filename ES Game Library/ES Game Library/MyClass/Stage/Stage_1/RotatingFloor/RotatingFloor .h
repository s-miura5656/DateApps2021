/**
 * @file Floor.h
 * @brief ステージベースを継承した外壁のクラス
 * @author 岩井瑞希
 * @date 2020/11/11
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"

class RotatingFloor :public StageBase
{
public:
	RotatingFloor(std::string tag);
	~RotatingFloor();
	bool Initialize() override;
	int Update() override;
	void Draw3D() override;
	Vector3 GetRot() { return front; }
private:
	float rotation;
	Vector3 front;
	bool flag;
	bool isHitEnter = false;
	bool PlayerHitCheck();
};