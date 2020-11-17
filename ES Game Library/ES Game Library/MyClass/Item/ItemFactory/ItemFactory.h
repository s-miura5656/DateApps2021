#pragma once
#pragma once

//�w�b�_�[�t�@�C���ǉ�
#include "../../../ESGLib.h"
#include "../../Managers/ItemManager/ItemManager.h"

//�A�C�e���w�b�_�[�t�@�C���ǉ�
#include "../AttackPowerItem/AttackPowerItem.h"
#include "../SpeedItem/SpeedItem.h"
#include "../HitPointItem/HitPointItem.h"


/**
*  @brief FACTORY�f�U�C���p�^�[��
*/

/**
 *  @brief ����_ENEMY_FACTORY�N���X
 */

class ItemFactory
{
public:
	ItemFactory() {};
	virtual ~ItemFactory() {};

	/**
	 *  @brief object�𐶐����A���̃C���X�^���X��Ԃ��֐�
	 */
	ItemBase* Create(std::string tag, Vector3 position);

	/**
	 *  @brief Product���쐬���鏃�����z�֐�
	 *  @param type Product�̎��
	 *  @param name Product�̏��L�҂̖��O
	 */
	virtual ItemBase* CreateProduct(std::string tag, Vector3 position) = 0;

};

class ItemStationeryFactory : public ItemFactory
{
public:
	/**
	 * @brief Product���쐬����֐�
	 */
	ItemBase* CreateProduct(std::string tag, Vector3 position);
};