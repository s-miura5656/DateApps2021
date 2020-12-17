#pragma once
#include "../../ESGLib.h"
#include <functional>

using namespace std;

class HitBox {
public:
	//�f�X�g���N�^
	virtual ~HitBox();

	//������
	virtual void Init();

	//�`��
	virtual void Draw3D();

	//�p�����[�^��ݒ�
	virtual void SetHitBox(float width, float height, float depth);

	//�������ɌĂ΂�鏈��
	void HitBox::OnReMove();

	void SetHitBoxScale(float sca);	
	void SetHitBoxScale(Vector3 sca);

	void SetHitBoxPosition(Vector3 pos);

	//���g��Ԃ�
	HitBox* GetThisHitBox() { return this; };

	//�Փ˂��Ă���HitBox�̃��X�g���擾
	std::list<HitBox*> HitBox::HitHitBoxlist();

	void    Settags(std::string tags);
	void    SetColor(Vector3 colors);
	void	SetModelScale();
	void    SetModelPosition();
	void    HitBoxMove(Vector3 move);

	Vector3 GetHitBoxPosition() const { return _model->GetPosition(); };
	Vector3 GetHitBoxScale() const { return _model->GetScale(); }

	HitBox* TypeRayRange(std::string tag, Vector3 position, Vector3 angle, float& range);
	HitBox* GetHitBoxTag(std::string tag);
	MODEL   GetModelTag() const { return _model; }
	bool    Tag_Sarch(std::string _tag);

	bool IsHitObjects(std::string tags);
	bool IsHitObjectsSquare(std::string tags);
	HitBox* IsHitObjectsPointer(std::string tags);

	Vector3 WallShavingObjects(std::list<HitBox*> is_hit_list, Vector3 pos, Vector3 front_vec);

	MODEL IshitNearestObject(std::list<HitBox*> is_hit_list, Vector3 pos, Vector3 front_vec);

	std::list<HitBox*> IsHitBoxList();
	std::list<HitBox*> IsHitBoxList(std::string tag);
	std::list<HitBox*> GetHitBoxList() const { return _HitBox_list; }
	std::string GetTag() const { return _tag; }

private:
	//�S�Ă�HitBox���i�[���Ă������X�g
	static std::list<HitBox*> _HitBox_list;

	std::string _tag;
	//����p�̃��f��
	static MODEL _model;

	//�p�����[�^
	float _width  = 1.0f;
	float _height = 1.0f;
	float _depth  = 1.0f;

	Vector3 _position;
	Vector3 _scale = Vector3_One;

	Vector3 _color = Vector3(1.0f, 0.0f, 0.0f);

	//�Փ˔���֐�
	bool HitBox::IsHit(HitBox* other);
protected:
	
};