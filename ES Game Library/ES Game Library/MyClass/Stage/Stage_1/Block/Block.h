/**
 * @file Block.h
 * @brief ステージベースを継承した破壊できるブロックのクラス
 * @author 岩井瑞希
 * @date 2020/11/11
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"
#include"../../../Item/ItemCounter/ItemCounter.h"
#include"../../../Data/WordsTable.h"
class Block :public StageBase
{
public:
	Block();
	~Block();
	bool Initialize() override;
	void Draw3D() override;
	void SetDestructiveFlag(bool destructiveflag) { _destructiveflag = destructiveflag; }
	bool GetDestructiveFlag() { return _destructiveflag; }
private:
	ItemCounter* itemcounter;
	bool _destructiveflag;
};