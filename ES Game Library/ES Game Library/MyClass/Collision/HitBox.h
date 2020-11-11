#pragma once
#include "../../ESGLib.h"
#include <functional>

class HitBox {
public:
	//�f�X�g���N�^
	virtual HitBox::~HitBox();

	//������
	virtual void HitBox::Init();

	//�`��
	virtual void HitBox::Draw3D();
	virtual void HitBox::DrawAlpha3D();

	//�p�����[�^��ݒ�
	virtual void HitBox::SetHitBox(float width, float height, float depth);

	//�������ɌĂ΂�鏈��
	void HitBox::OnReMove();

	void SetHitBoxScale(float sca);	
	void SetHitBoxScale(Vector3 sca);

	void SetHitBoxPosition(Vector3 pos);

	//���g��Ԃ�
	HitBox* HitBox::GetThisHitBox() { return this; };

	//�Փ˂��Ă���HitBox�̃��X�g���擾
	std::list<HitBox*> HitBox::HitHitBoxlist();

	void    Settags(string tags);
	void    SetColor(Vector3 colors);
	void    HitBoxMove(Vector3 move);

	Vector3 GetHitBoxPosition()const { return _model->GetPosition(); };

	HitBox* HitBox::TypeRayRange(std::string tag, Vector3 position, Vector3 angle, float& range);
	HitBox* HitBox::Get_Tag_HitBox(std::string tag);
	MODEL   HitBox::Get_Tag_Model() const { return _model; };
	bool    HitBox::Tag_Sarch(string _tag);

	bool HitBox::IsHitObjects(std::string tags);

	string tag;
private:
	//�S�Ă�HitBox���i�[���Ă������X�g
	static std::list<HitBox*> _HitBox_list;

	//����p�̃��f��
	MODEL _model = nullptr;

	//�p�����[�^
	float _width = 1.0f;
	float _height = 1.0f;
	float _depth = 1.0f;

	Vector3 position;
	Vector3    scale;

	Vector3 color = Vector3(1.0f, 0.0f, 0.0f);

	//�Փ˔���֐�
	bool HitBox::IsHit(HitBox* other);

protected:
	
};