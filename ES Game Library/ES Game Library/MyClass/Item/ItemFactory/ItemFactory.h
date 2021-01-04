#pragma once
#pragma once

//ヘッダーファイル追加
#include "../../../ESGLib.h"
#include "../../Managers/ItemManager/ItemManager.h"

//アイテムヘッダーファイル追加
#include "../AttackPowerItem/AttackPowerItem.h"
#include "../SpeedItem/SpeedItem.h"
#include "../HitPointItem/HitPointItem.h"
#include "../PointItem/PointItem.h"

/**
*  @brief FACTORYデザインパターン
*/

/**
 *  @brief 抽象_ENEMY_FACTORYクラス
 */

class ItemFactory
{
public:
	ItemFactory() {};
	virtual ~ItemFactory() {};

	/**
	 *  @brief objectを生成し、そのインスタンスを返す関数
	 */
	ItemBase* Create(std::string tag, Vector3 position, int point);

	/**
	 *  @brief Productを作成する純粋仮想関数
	 *  @param type Productの種類
	 *  @param name Productの所有者の名前
	 */
	virtual ItemBase* CreateProduct(std::string tag, Vector3 position, int point) = 0;

};

class ItemStationeryFactory : public ItemFactory
{
public:
	/**
	 * @brief Productを作成する関数
	 */
	ItemBase* CreateProduct(std::string tag, Vector3 position, int point);
};