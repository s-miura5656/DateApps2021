#include "HitBox.h"

//static
std::list<HitBox*> HitBox::_HitBox_list;
//�f�X�g���N�^
HitBox::~HitBox() {
	OnReMove();
}
void HitBox::Init() {
	//HitBox����
	SetHitBox(1.f, 1.f, 1.f);
	//���������X�g�ɑ}��
	_HitBox_list.push_back(this);

	//�^�O�ݒ�
	tag = "HitBox";
};

void HitBox::Draw3D() {
	_model->SetScale(scale);
#if _DEBUG
	//_model->Draw();
#endif
}
void HitBox::DrawAlpha3D() {
	//
}

void HitBox::Settags(string tags) {
	tag = tags;
}

//�q�b�g�{�b�N�X����
void HitBox::SetHitBox(float width, float height, float depth) {
	//�p�����[�^�ݒ�
	_width = width;
	_height = height;
	_depth = depth ;
	//Model�ݒ�
	SimpleShape   shape;
	shape.Type = Shape_Box;
	shape.Width = _width;
	shape.Height = _height;
	shape.Depth = _depth;
	_model = GraphicsDevice.CreateModelFromSimpleShape(shape);
	//Material�ݒ�
	Material _mtrl;
	_mtrl.Emissive = Color(color);
	_model->SetMaterial(_mtrl);
}

void HitBox::SetColor(Vector3 colors) {
	Material _mtrl;
	_mtrl.Emissive = Color(colors);
	_model->SetMaterial(_mtrl);
}

void HitBox::HitBoxMove(Vector3 move)
{
	_model->Move(move);
}

// �������ɌĂ΂�鏈��
void HitBox::OnReMove() {
	auto it = _HitBox_list.begin();
	while (it != _HitBox_list.end()) {
		if ((*it) != this) {
			it++;
		}
		else {
			it = _HitBox_list.erase(it);
			return;
		}
	}
}

bool HitBox::IsHit(HitBox* other) {
	OrientedBoundingBox model_obb1 = this->_model->GetOBB();
	OrientedBoundingBox model_obb2 = other->_model->GetOBB();
	return model_obb1.Intersects(model_obb2);
}

std::list<HitBox*> HitBox::HitHitBoxlist() {
	std::list<HitBox*>  result;
	for (auto&& h : _HitBox_list) {
		//�����Ƃ͔��肵�Ȃ�
		
		if (h->GetThisHitBox() == this) continue;
		if (h->IsHit(this)) result.push_back(h->GetThisHitBox());
	}
	return result;
};

//�^�O����������
bool HitBox::Tag_Sarch(string _tag)
{
	bool f = false;
	for (auto&& h : _HitBox_list) {
		if (h->tag == _tag) { f = true; };
	}
	return f;
}

void HitBox::SetHitBoxPosition(Vector3 pos) {
	_model->SetPosition(pos);
}

void HitBox::SetHitBoxScale(float sca) {
	scale = Vector3_One * sca;
}

void HitBox::SetHitBoxScale(Vector3 sca)
{
	scale = sca;
}


//�w�������Ray���΂��Փ˂����w��^�O�̃I�u�W�F�N�g��e�Ɏ���HitBox���������������ł��߂�HitBox���擾
HitBox* HitBox::TypeRayRange(std::string tag, Vector3 position, Vector3 angle, float& range) {

	range = 99999.0f;
	HitBox* p_result = nullptr;

	for (auto&& other : _HitBox_list) {
		//�^�O���قȂ�ꍇ�������J�b�g
		if (other->tag != tag) continue;
		//���g�Ƃ͔�����s��Ȃ�
		if (this == other->GetThisHitBox())  continue;
		//�������擾
		float _range = 0.0f;// = other->RayRange(this->GetThisHitBox(), angle);
		//other->_model->IntersectRay(this->_model->GetPosition(), angle, &_range);
		other->_model->IntersectRay(position, angle, &_range);
		//�擾�ł��Ȃ������ꍇ�������J�b�g
		if (_range <= 0.0f)  continue;
		//�������ŏ��l�̂��̂ɍX�V
		if (_range < range) {
			range = _range;
			p_result = other->GetThisHitBox();
		}
	}
	return  p_result;
}

/**
 * @fn
 * @param (std::string tag) �����̐��� �~�����q�b�g�{�b�N�X�̃^�O
 * @return �߂�l�̐����@�q�b�g�{�b�N�X���擾�Ԃ�
 * @detail �ڍׂȐ����@�O���ɂ���q�b�g�{�b�N�X���擾�ł���
 */
HitBox* HitBox::Get_Tag_HitBox(std::string tag)
{
	ASSERT(Tag_Sarch(tag) && "tag�����݂��Ă��Ȃ�!");
	HitBox* hitbox = nullptr;
	for (auto&& other_hitbox : _HitBox_list)
	{
		if (other_hitbox->tag != tag) continue;
		//�^�O�ȊO��e��
		if (this == other_hitbox->GetThisHitBox()) continue;
		//������e��
		hitbox = other_hitbox->GetThisHitBox();
	}

	return hitbox != nullptr ? hitbox : nullptr;
}

/**
 * @fn
 * @param (std::string tags) �����̐����@�Փ˔�����������^�O��������
 * @return �߂�l�̐����@�������Ă����TRUE�@�������ĂȂ�������FALSE
 */
bool HitBox::IsHitObjects(std::string tags) {
	ASSERT(Tag_Sarch(tags) && "tag�����݂��Ă��Ȃ�!");
	bool result = false;
	std::list<HitBox*> HitList = HitHitBoxlist();
	for (auto&& other : HitList) {
		if (other->tag == tags) {
			result = true;
		}
	}
	return result;
}
