/**
 * @file Pillar.h
 * @brief ステージベースを継承した破壊できないブロックのクラス
 * @author 岩井瑞希
 * @date 2020/11/11
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"

class Pillar :public StageBase
{
public:
	Pillar(std::string tag);
	~Pillar();
	bool Initialize() override;


private:
};