#pragma once
#pragma once

//ヘッダーファイル追加
#include "../../ESGLib.h"
#include "../Managers/ItemManager/ItemManager.h"

//アイテムヘッダーファイル追加
#include "../Item/SpeedItem/SpeedItem.h"
#include "../Item/AttackPowerItem/AttackPowerItem.h"
#include"../Item/HitPointItem/HitPointItem.h"


/**
*  @brief FACTORYデザインパターン
*/

/**
 *  @brief 抽象_ENEMY_FACTORYクラス
 */

class CItemFactory
{
public:
	CItemFactory() {};
	virtual ~CItemFactory() {};

	/**
	 *  @brief objectを生成し、そのインスタンスを返す関数
	 */
	ItemBase* Create(std::string _type, Vector3 _position);

	/**
	 *  @brief Productを作成する純粋仮想関数
	 *  @param type Productの種類
	 *  @param name Productの所有者の名前
	 */
	virtual ItemBase* CreateProduct(std::string _type, Vector3 _position) = 0;

};

class ItemStationeryFactory : public CItemFactory
{
public:
	/**
	 * @brief Productを作成する関数
	 */
	ItemBase* CreateProduct(std::string _type, Vector3 _position);
};