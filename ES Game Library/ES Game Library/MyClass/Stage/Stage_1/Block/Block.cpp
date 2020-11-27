#include"Block.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"

Block::Block(std::string tag)
{
	_model = nullptr;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_tag = tag;
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(1.f);
}

Block::~Block()
{
	_hit_box.reset();
}

bool Block::Initialize()
{
	//X�t�@�C���̓ǂݍ���
	//_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/capsule.X"));
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/capsule.X"));
	//�X�P�[���̐ݒ�
	_model->SetScale(_scale);
	//�}�e���A���̐ݒ�
	_model->SetMaterial(GetMaterial());
	//�����蔻���j��\�u���b�N�Ɠ����|�W�V�����ɂ���
	_hit_box->SetHitBoxPosition(_position);
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
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		if (_hit_box->IsHitObjects(name))
		{
			return 1;
		}
	}

	return 0;
}
