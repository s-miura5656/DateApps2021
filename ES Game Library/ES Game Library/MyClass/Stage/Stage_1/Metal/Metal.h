/**
 * @file Floor.h
 * @brief ステージベースを継承した外壁のクラス
 * @author 岩井瑞希
 * @date 2020/11/11
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"

class Metal :public StageBase
{
public:
	Metal(std::string tag);
	~Metal();
	bool Initialize() override;


private:
};