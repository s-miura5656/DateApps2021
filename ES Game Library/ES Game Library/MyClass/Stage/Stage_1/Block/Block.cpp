#include "Block.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Data/IData.h"
#include "../../../Data/WordsTable.h"
#include "../../../Managers/SceneManager/SceneManager.h"
#include "../../../ParticleSystem/Particle.h"

Block::Block(std::string tag)
{
	_model  = nullptr;
	_tag = tag;
}

Block::~Block()
{
	_hit_box.reset();
	_effect.reset();
}

bool Block::Initialize()
{
	_effect.reset(new ParticleSystem);
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(1.0f);

	//X�t�@�C���̓ǂݍ���
	_model  = ResouceManager::Instance().LoadModelFile(_T("MapSprite/capsule2.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StandardShader.hlsl"));
	auto effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/effekseer_break02/break_effect.efk"));

	_effect->RegisterParticle(effect);
	_effect->SetSpeed(1.0f);
	_effect->SetScale(1.0f);

	//�X�P�[���̐ݒ�
	_scale = 0.85f;
	_model->SetScale(_scale);
	//�}�e���A���̐ݒ�
	
	//�����蔻���j��\�u���b�N�Ɠ����|�W�V�����ɂ���
	_hit_box->SetHitBoxPosition(_position + Vector3(0, 1, 0));

	_handle = INT_MAX;

	if (_position.y > 0)
	{
		_blinking = new Blinking;
		_blinking->Initialize(_position);
	}

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
	if (_position.y > 0)
	{
		Fall();
	}

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

			_effect->SetPosition(_position + Vector3_Up * 0.5f);
			_effect->PlayOneShot();

			return 1;
		}
	}
	return 0;
}

void Block::Draw3D()
{
	if (_hit_box != nullptr)
	{
		_hit_box->SetModelPosition();
		_hit_box->SetModelScale();
		//_hit_box->Draw3D();
	}
	if (_position.y > 0)
	{
		_blinking->Draw3D();
	}
	_effect->Draw();
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
/**
 * @fn �~���Ă���Ƃ��̃u���b�N�̏���
 * @detail  �u���b�N�����ɓ�����
 *          �u���b�N��Y���W��0�ɂȂ�����mapdata�Ɏ����̍��W��ۑ�����
 *          �v���C���[�Ƃ̐ڐG���Ƀv���C���[��|��
 */
void Block::Fall()
{
	//TODO:�~���Ă��鑬���͒�������
	_position.y -= 0.05;

	//!Y���W��0�ɂȂ����Ƃ��Ɏ����̍��W���}�b�v�f�[�^���Z�b�g����
	if (_position.y <= 0)
	{
		IMapData* map_data = new IMapData;
		auto data = map_data->GetData();

		int x = fabsf(_position.x);
		int z = fabsf(_position.z);

		data[z][x] = 'b';
		map_data->SetData(data);
		delete map_data;
		delete _blinking;
	}

	_hit_box->SetHitBoxPosition(_position + Vector3(0, 1, 0));

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string player_tag = PLAYER_TAG + std::to_string(i + 1);

		//!�v���C���[�Ƃ̐ڐG���Ƀv���C���[��|��
		if (_hit_box->IsHitObjectsSquare(player_tag))
		{
			IPrayerData* iplayerdata = new IPrayerData;
			iplayerdata->SetState(player_tag, PlayerEnum::Animation::DEATH);
			delete iplayerdata;
		}

	}
	_blinking->Update();
}