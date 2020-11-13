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

	virtual bool Initialize() { return true; };
	virtual int Update();
	virtual void Draw3D();
	Material GetMaterial();

	//引数でステージを構成するブロックのポジションをセットする
	void SetPosition(Vector3& position) { _position = position; }
	//ステージを構成するブロックのポジションを取得する
	Vector3 GetPosition() { return _position; }
	//ステージを構成するブロックの破壊フラグをセットする
	void SetDestructionFlag(bool& destruction_flag) { _destruction_flag = destruction_flag; }
	//ステージを構成するブロックの破壊フラグを取得する
	bool GetDestructionFlag() { return _destruction_flag; }
protected:
	const float scale = 0.0254f;//!基準のスケールを設定する
	bool _destruction_flag = true;//!falseで破壊される破壊フラグ
	MODEL block_base;//!継承されるモデルのベース
	Vector3 _position;//!継承されるモデルのポジション
private:

};