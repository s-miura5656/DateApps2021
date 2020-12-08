#include "HitBox.h"
#include "../Data/MyAlgorithm.h"

//static
std::list<HitBox*> HitBox::_HitBox_list;

MODEL HitBox::_model = nullptr;

//�f�X�g���N�^
HitBox::~HitBox() 
{
	OnReMove();
}

void HitBox::Init() {
	//HitBox����
	SetHitBox(1.f, 1.f, 1.f);

	//���������X�g�ɑ}��
	_HitBox_list.push_back(this);

	//�^�O�ݒ�
	_tag = "HitBox";
};

void HitBox::Draw3D() 
{
#if _DEBUG
	GraphicsDevice.BeginAlphaBlend();
	_model->DrawAlpha(0.5f);
	GraphicsDevice.EndAlphaBlend();
#endif
}

void HitBox::SetScale()
{
	_model->SetScale(_scale);
}

void HitBox::Settags(string tags) 
{
	_tag = tags;
}

//�q�b�g�{�b�N�X����
void HitBox::SetHitBox(float width, float height, float depth) 
{
	//�p�����[�^�ݒ�
	_width  = width;
	_height = height;
	_depth  = depth ;

	//Model�ݒ�
	if (_model == nullptr )
	{
		SimpleShape   shape;
		shape.Type   = Shape_Box;
		shape.Width  = _width;
		shape.Height = _height;
		shape.Depth  = _depth;
		_model = GraphicsDevice.CreateModelFromSimpleShape(shape);
	}

	//Material�ݒ�
	Material _mtrl;
	_mtrl.Diffuse = Color(1.f, 1.f, 1.f);
	_mtrl.Ambient = Color(1.f, 1.f, 1.f);
	_mtrl.Specular = Color(1.f, 1.f, 1.f);
	_model->SetMaterial(_mtrl);
}

void HitBox::SetColor(Vector3 colors) {
	Material _mtrl;
	_mtrl.Diffuse = Color(1.f, 1.f, 1.f);
	_mtrl.Ambient = Color(1.f, 1.f, 1.f);
	_mtrl.Specular = Color(1.f, 1.f, 1.f);
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
		if (h->_tag == _tag) { f = true; };
	}
	return f;
}

void HitBox::SetHitBoxPosition(Vector3 pos) {
	_position = pos;
	_model->SetPosition(pos);
}

void HitBox::SetHitBoxScale(float sca) {
	_scale = Vector3_One * sca;
}

void HitBox::SetHitBoxScale(Vector3 sca)
{
	_scale = sca;
}


//�w�������Ray���΂��Փ˂����w��^�O�̃I�u�W�F�N�g��e�Ɏ���HitBox���������������ł��߂�HitBox���擾
HitBox* HitBox::TypeRayRange(std::string tag, Vector3 position, Vector3 angle, float& range) {

	range = 99999.0f;
	HitBox* p_result = nullptr;

	if (tag == "WallMetal_0")
	{
		int i = 0;
	}

	for (auto&& other : _HitBox_list) {
		//�^�O���قȂ�ꍇ�������J�b�g
		if (other->_tag != tag) continue;
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
HitBox* HitBox::GetHitBoxTag(std::string tag)
{
	ASSERT(Tag_Sarch(tag) && "tag�����݂��Ă��Ȃ�!");
	HitBox* hitbox = nullptr;
	for (auto&& other_hitbox : _HitBox_list)
	{
		if (other_hitbox->_tag != tag) continue;
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
	for (auto&& other : HitList) 
	{
		if (other->_tag == tags)
			result = true;
	}
	return result;
}

/**
 * @fn �����蔻��
 * @brief OBB���g�p���������蔻���BOX��p��������
 * @param (std::string tags) �Փ˔�����������^�O��������
 * @return �߂�l�̐����@�������Ă����TRUE�@�������ĂȂ�������FALSE
 */
bool HitBox::IsHitObjectsSquare(std::string tags)
{
	bool result = false;

	HitBox* hit_object;

	float dist = FLT_MAX;

	std::vector<float> dists;

	for (auto it = _HitBox_list.begin(); it != _HitBox_list.end(); ++it)
	{
		//! �����͔�΂��Ď���
		if ((*it)->_tag == this->_tag)
			continue;

		//! �T���Ă��� HitBox* �������������烋�[�v�𔲂���
		if ((*it)->_tag == tags)
		{
			hit_object = (*it);
			break;
		}
	}

	//! �����蔻����s���Ă�����̃��f���̍��W�ƃT�C�Y
	auto a_pos   = this->_position;
	auto a_scale = this->_model->GetScale() / 2;

	//! �������Ă�����̍��W�ƃT�C�Y
	auto b_pos   = hit_object->_position;
	auto b_scale = hit_object->_model->GetScale() / 2;

	//! a��b�̃{�b�N�X�̓����蔻��
	if (a_pos.x - a_scale.x < b_pos.x + b_scale.x &&
		a_pos.x + a_scale.x > b_pos.x - b_scale.x &&
		a_pos.y - a_scale.y < b_pos.y + b_scale.y && 
		a_pos.y + a_scale.y > b_pos.y - b_scale.y &&
		a_pos.z - a_scale.z < b_pos.z + b_scale.z && 
		a_pos.z + a_scale.z > b_pos.z - b_scale.z)
	{
		result = true;
	}

	return result;
}

HitBox* HitBox::IsHitObjectsPointer(std::string tags) {
	
	HitBox* result = nullptr;

	if (!Tag_Sarch(tags))
		return result = nullptr;

	std::list<HitBox*> HitList = HitHitBoxlist();
	for (auto&& other : HitList)
	{
		if (other->_tag == tags)
			return result = other;
	}

	return result = nullptr;
}

/**
 * @fn �ǂ���x�N�g���̎擾
 * @param (is_hit_list) �������Ă���q�b�g�{�b�N�X�̃��X�g���擾
 * @param (pos) �ǂ��肳�������Ώۂ̍��W
 * @param (move_dir) �ǂ��肳�������Ώۂ̌����x�N�g��
 * @return �߂�l�̐����@�ǂ���̃x�N�g��
 */
Vector3 HitBox::WallShavingObjects(std::list<HitBox*> is_hit_list, Vector3 pos, Vector3 move_dir)
{
	float dist = FLT_MAX;

	std::vector<float> dists;

	for (auto it = is_hit_list.begin(); it != is_hit_list.end(); ++it)
	{
		(*it)->GetModelTag()->IntersectRay(pos, move_dir, &dist);
		dists.push_back(dist);
	}

	auto it = std::min_element(dists.begin(), dists.end());

	int index = std::distance(dists.begin(), it);

	auto box = std::next(is_hit_list.begin(), index);

	Vector3 _normal = Vector3_Zero;

	auto model = (*box)->GetModelTag();

	pos = model->GetPosition();

	model->IntersectRay(pos, move_dir, nullptr, &_normal);

	Vector3 dir = move_dir + Vector3_Dot(-move_dir, _normal) * _normal;

	return dir;
}

MODEL HitBox::IshitNearestObject(std::list<HitBox*> is_hit_list, Vector3 pos, Vector3 move_dir)
{
	float dist = FLT_MAX;

	std::vector<float> dists;

	for (auto it = is_hit_list.begin(); it != is_hit_list.end(); ++it)
	{
		(*it)->GetModelTag()->IntersectRay(pos, move_dir, &dist);
		dists.push_back(dist);
	}

	auto it = std::min_element(dists.begin(), dists.end());

	int index = std::distance(dists.begin(), it);

	auto box = std::next(is_hit_list.begin(), index);

	return (*box)->GetModelTag();
}



/**
 * @fn �������Ă���q�b�g�{�b�N�X���擾
 * @return �������Ă���q�b�g�{�b�N�X�����X�g�Ƃ��ĕԂ�
 */
std::list<HitBox*> HitBox::IsHitBoxList() {
	std::list<HitBox*> HitList = HitHitBoxlist();
	return HitList;
}

/**
 * @fn �������Ă���q�b�g�{�b�N�X���擾
 * @param (tag) �^�O�̃q�b�g�{�b�N�X�����O����
 * @return �������Ă���q�b�g�{�b�N�X�����X�g�Ƃ��ĕԂ�
 */
std::list<HitBox*> HitBox::IsHitBoxList(std::string tag)
{
	std::list<HitBox*> HitList = HitHitBoxlist();
	
	auto&& it = HitList.begin();
	while (it != HitList.end())
	{
		if ((*it)->_tag == tag)
		{
			it = HitList.erase(it);
			continue;
		}
		it++;
	}
	return HitList;
}
