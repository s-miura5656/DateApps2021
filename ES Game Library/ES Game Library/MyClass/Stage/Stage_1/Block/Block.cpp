#include "Block.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Data/IData.h"

Block::Block(std::string tag)
{
	_model = nullptr;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_tag = tag;
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(0.9f);
}

Block::~Block()
{
	_hit_box->OnReMove();
}

bool Block::Initialize()
{
	//X�t�@�C���̓ǂݍ���
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/capsule.X"));
	//�X�P�[���̐ݒ�
	_model->SetScale(_scale);
	//�}�e���A���̐ݒ�
	_model->SetMaterial(GetMaterial());
	//�����蔻���j��\�u���b�N�Ɠ����|�W�V�����ɂ���
	_hit_box->SetHitBoxPosition(_position + Vector3(0,1,0));
	return _model != nullptr;
}
/**
 * @brief �v���C���[���G�ꂽ���̏���
 * @return �v���C���[���G��ĂȂ��� (int)0
 * @return �v���C���[���G�ꂽ�� (int)1
 */
int Block::Update()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string arm_tag = ARM_TAG + std::to_string(i + 1);
		
		if (!_hit_box->Tag_Sarch(arm_tag))
			continue;

		if (_hit_box->IsHitObjects(arm_tag)) 
		{
			IMapData* mapdata = new IMapData;
			auto data = mapdata->GetData();

			int x = fabsf(_position.x);
			int z = fabsf(_position.z);

			data[z][x] = ' ';
			mapdata->SetData(data);
			delete mapdata;
			return 1;
		}
	}
	return 0;
}
