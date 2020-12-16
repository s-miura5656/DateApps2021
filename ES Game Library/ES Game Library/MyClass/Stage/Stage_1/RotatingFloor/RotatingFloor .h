/**
 * @file Floor.h
 * @brief ステージベースを継承した矢印床のクラス
 * @author 岩井瑞希
 * @date 2020/12/11
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"

class RotatingFloor : public StageBase
{
public:
	RotatingFloor(std::string tag);
	~RotatingFloor();
	bool Initialize() override;
	int Update() override;
	void Draw3D() override;
	Vector3 GetRot() { return front; }
private:
	void orthodontics();
	float rotation;
	Vector3 front;
	bool flag;
	bool isHitEnter = false;
	bool PlayerHitCheck();
};