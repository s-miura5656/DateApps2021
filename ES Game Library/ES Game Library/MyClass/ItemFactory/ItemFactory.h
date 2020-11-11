#pragma once
#pragma once

//�w�b�_�[�t�@�C���ǉ�
#include "../../ESGLib.h"
#include "../Managers/ItemManager/ItemManager.h"

//�A�C�e���w�b�_�[�t�@�C���ǉ�
#include "../Item/SpeedItem/SpeedItem.h"
#include "../Item/AttackPowerItem/AttackPowerItem.h"
#include"../Item/HitPointItem/HitPointItem.h"


/**
*  @brief FACTORY�f�U�C���p�^�[��
*/

/**
 *  @brief ����_ENEMY_FACTORY�N���X
 */

class CItemFactory
{
public:
	CItemFactory() {};
	virtual ~CItemFactory() {};

	/**
	 *  @brief object�𐶐����A���̃C���X�^���X��Ԃ��֐�
	 */
	ItemBase* Create(std::string _type, Vector3 _position);

	/**
	 *  @brief Product���쐬���鏃�����z�֐�
	 *  @param type Product�̎��
	 *  @param name Product�̏��L�҂̖��O
	 */
	virtual ItemBase* CreateProduct(std::string _type, Vector3 _position) = 0;

};

class ItemStationeryFactory : public CItemFactory
{
public:
	/**
	 * @brief Product���쐬����֐�
	 */
	ItemBase* CreateProduct(std::string _type, Vector3 _position);
};