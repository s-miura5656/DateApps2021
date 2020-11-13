/**
 * @file Floor.h
 * @brief ステージベースを継承した床のクラス
 * @author 岩井瑞希
 * @date 2020/11/11
 */
#pragma once

#include"../../../ESGLib.h"
#include"../StageBase.h"
class Floor :public StageBase
{
public:
	Floor();
	~Floor();
	bool Initialize() override;
private:
};