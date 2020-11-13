/**
 * @file Block.h
 * @brief ステージベースを継承した破壊できるブロックのクラス
 * @author 岩井瑞希
 * @date 2020/11/11
 */
#pragma once

#include"../../../ESGLib.h"
#include"../StageBase.h"
class Block :public StageBase
{
public:
	Block();
	~Block();
	bool Initialize();
private:
};