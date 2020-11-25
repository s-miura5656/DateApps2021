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
	//引数でステージを構成するブロックのローテーションをセットする
	void SetRotation(Vector3& rotation) { _rotation = rotation; }
	//ステージを構成するブロックのポジションを取得する
	Vector3 GetPosition() { return _position; }
	bool IsFlag() const { return Removeflag; };
	std::string GetTag() const { return _tag; }
protected:
	const float _scale = 1.0f;//!基準のスケールを設定する
	MODEL _model;//!継承されるモデルのベース
	Vector3 _position;//!継承されるモデルのポジション
	Vector3 _rotation;//!継承されるモデルのローテーション
	std::unique_ptr<HitBox> _hit_box;
	std::string _tag;
	bool Removeflag = false;
private:

};