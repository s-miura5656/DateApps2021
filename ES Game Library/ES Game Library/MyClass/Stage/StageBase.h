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
	virtual void Draw3D();
	Material GetMaterial();

	void SetPosition(Vector3& position) { _position = position; }

	Vector3 GetPosition() { return _position; }

	void SetDestructionFlag(bool& destruction_flag) { _destruction_flag = destruction_flag; }

	bool GetDestructionFlag() { return _destruction_flag; }
protected:
	const float scale = 0.0254f;
	bool _destruction_flag;
	MODEL block_base;
	Vector3 _position;
private:

};