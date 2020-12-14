#include "Block.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Data/IData.h"
#include "../../../Data/WordsTable.h"
#include "../../../Managers/SceneManager/SceneManager.h"

Block::Block(std::string tag)
{
	_model = nullptr;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_tag = tag;
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(1.0f);
}

Block::~Block()
{
	_hit_box.reset();
	_effect->Stop(_handle);
}

bool Block::Initialize()
{
	//X�t�@�C���̓ǂݍ���
	_model  = ResouceManager::Instance().LoadModelFile(_T("MapSprite/capsule2.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StandardShader.hlsl"));
	_effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/effekseer_break02/break_effect.efk"));
	
	//�X�P�[���̐ݒ�
	_scale = 0.85f;
	_model->SetScale(_scale);
	//�}�e���A���̐ݒ�
	
	//�����蔻���j��\�u���b�N�Ɠ����|�W�V�����ɂ���
	_hit_box->SetHitBoxPosition(_position + Vector3(0, 1, 0));

	_handle = INT_MAX;

	//! shader
	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);
	

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
		std::string arm_tag    = ARM_TAG + std::to_string(i + 1);
		std::string player_tag = PLAYER_TAG + std::to_string(i + 1);

		if (!_hit_box->Tag_Sarch(arm_tag))
			continue;

		if (_hit_box->IsHitObjectsSquare(arm_tag)) 
		{
			IArmData* arm_data = new IArmData;
			int state = arm_data->GetState(arm_tag);
			if (state == ArmEnum::PunchState::RETURN_PUNCH)
			{
				delete arm_data;
				return 0;
			}
				

			IMapData* map_data = new IMapData;
			auto data = map_data->GetData();

			int x = fabsf(_position.x);
			int z = fabsf(_position.z);

			data[z][x] = ' ';
			map_data->SetData(data);
			delete map_data;

			arm_data->SetState(arm_tag, ArmEnum::PunchState::RETURN_PUNCH);
			delete arm_data;

			IPrayerData* player_data = new IPrayerData;
			player_data->SetRankingPoint(player_tag, player_data->GetRankingPoint(player_tag) + 10);
			delete player_data;

			_handle = _effect->Play(_position + Vector3(0, 0.5f, 0));

			return 1;
		}
	}

	return 0;
}

void Block::Draw3D()
{
	_effect->SetSpeed(_handle, 0.5f);
	_effect->SetScale(_handle, 1.0f);

	if (_hit_box != nullptr)
	{
		_hit_box->SetModelPosition();
		_hit_box->SetModelScale();
		//_hit_box->Draw3D();
	}
}

void Block::DrawAlpha3D()
{
	Material mat;
	mat.Diffuse = Color(0.5f, 0.5f, 0.5f);
	mat.Ambient = Color(1.0f, 1.0f, 1.0f);
	mat.Specular = Color(0.5f, 0.5f, 0.5f);

	_model->SetMaterial(mat);
	_model->SetPosition(_position);
	_model->SetRotation(0, 0, 0);

	Matrix world = _model->GetWorldMatrix();
	_shader->SetParameter("model_ambient", _model->GetMaterial().Ambient);
	_shader->SetParameter("wvp", world * SceneCamera::Instance().GetCamera().GetViewProjectionMatrix());
	_shader->SetParameter("eye_pos", SceneCamera::Instance().GetCamera().GetPosition());
	_shader->SetTechnique("FixModel_S0");
	_model->Draw(_shader);
}
