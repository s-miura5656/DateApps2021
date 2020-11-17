//! @file   StageBase.h
//! @brief  ステージ用の基底クラス
//! @author Souta_Miura
//! @date   2020/11/09
#pragma once

#include "../../ESGLib.h"
#include "../Collision/HitBox.h"

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
protected:
	const float _scale = 0.0254f;//!基準のスケールを設定する
	MODEL _model;//!継承されるモデルのベース
	Vector3 _position;//!継承されるモデルのポジション
	std::unique_ptr<HitBox> _hit_box;
	std::string _tag;
private:

};