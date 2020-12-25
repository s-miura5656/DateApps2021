//! @file   StageBase.h
//! @brief  �X�e�[�W�p�̊Ǘ��N���X
//! @author Souta_Miura
//! @date   2020/11/09
#pragma once

#include"../../Managers/ManagerBase.h"
#include"../../Stage/Stage_1/Block/Block.h"
#include"../../Stage/Stage_1/Indestructible/Indestructible.h"
#include"../../Stage/Stage_1/RotatingFloor/RotatingFloor .h"
#include"../../Stage/Stage_1/Warp/Warp.h"
class StageBase;
class HitBox;


class StageManager : public ManagerBase
{
public:
	StageManager();
	~StageManager();

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override;

private:
	ItemCounter*                _itemcounter;
	std::vector<StageBase*>	    _stages;
	std::vector<cstring>		_mapdate; //! �}�b�v�f�[�^�̓ǂݍ���
	SPRITE                      _bg_sprite;
	string                      _random_item[3];
	int                         _count;
	int                         _probability;	
};