//! @file   StageBase.h
//! @brief  ステージ用の基底クラス
//! @author Souta_Miura
//! @date   2020/11/09

#pragma once

#include "../../ESGLib.h"

class StageBase
{
public:
	StageBase();
	virtual ~StageBase();

	virtual bool Initialize();
	virtual int Update();
	virtual void Draw2D();
	virtual void Draw3D();

protected:
	const float scale = 0.0254f;
	MODEL block;//壊れない
	MODEL pillar;//壊れる
	MODEL map;//床
	int xz[15][19];//ファイルの読み込み
	char comma;//カンマ読み込み
private:

};