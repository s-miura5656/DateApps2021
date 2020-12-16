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

class ParticleSystem;

class Block :public StageBase
{
public:
	Block(std::string tag);
	~Block();
	bool Initialize() override;
	int Update() override;
	void Draw3D() override;
	void DrawAlpha3D() override;
private:
	ItemCounter* itemcounter;
	std::unique_ptr<ParticleSystem> _effect;
	int _handle;
};