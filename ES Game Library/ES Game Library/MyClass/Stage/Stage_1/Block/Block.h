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
#include"../Blinking/Blinking.h"
#include "../../../Data/IData.h"

class ParticleSystem;

class Block :public StageBase
{
public:
	Block(std::string tag,std::string item);
	~Block();
	bool Initialize() override;
	int Update() override;
	void Draw3D() override;
	void DrawAlpha3D() override;
private:
	void Fall();
	Blinking*                       _blinking;
	ItemCounter*                    _itemcounter;
	std::unique_ptr<ParticleSystem> _effect;
	std::string                     _item_name;
	std::unique_ptr<IArmData>		_i_arm_data;
	const int						_arm_distance = 2.5f;
	int                             _speed;
	int                             _player_point = 0;
};