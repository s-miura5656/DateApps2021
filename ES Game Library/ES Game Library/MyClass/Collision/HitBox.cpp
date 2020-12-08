#include "HitBox.h"
#include "../Data/MyAlgorithm.h"

//static
std::list<HitBox*> HitBox::_HitBox_list;

MODEL HitBox::_model = nullptr;

//デストラクタ
HitBox::~HitBox() 
{
	OnReMove();
}

void HitBox::Init() {
	//HitBox生成
	SetHitBox(1.f, 1.f, 1.f);

	//自分をリストに挿入
	_HitBox_list.push_back(this);

	//タグ設定
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

//ヒットボックス生成
void HitBox::SetHitBox(float width, float height, float depth) 
{
	//パラメータ設定
	_width  = width;
	_height = height;
	_depth  = depth ;

	//Model設定
	if (_model == nullptr )
	{
		SimpleShape   shape;
		shape.Type   = Shape_Box;
		shape.Width  = _width;
		shape.Height = _height;
		shape.Depth  = _depth;
		_model = GraphicsDevice.CreateModelFromSimpleShape(shape);
	}

	//Material設定
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

// 消去時に呼ばれる処理
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
		//自分とは判定しない
		if (h->GetThisHitBox() == this) continue;
		if (h->IsHit(this)) result.push_back(h->GetThisHitBox());
	}
	return result;
};

//タグを検索する
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


//指定方向にRayを飛ばし衝突した指定タグのオブジェクトを親に持つHitBoxを検索し距離が最も近いHitBoxを取得
HitBox* HitBox::TypeRayRange(std::string tag, Vector3 position, Vector3 angle, float& range) {

	range = 99999.0f;
	HitBox* p_result = nullptr;

	if (tag == "WallMetal_0")
	{
		int i = 0;
	}

	for (auto&& other : _HitBox_list) {
		//タグが異なる場合処理をカット
		if (other->_tag != tag) continue;
		//自身とは判定を行わない
		if (this == other->GetThisHitBox())  continue;
		//距離を取得
		float _range = 0.0f;// = other->RayRange(this->GetThisHitBox(), angle);
		//other->_model->IntersectRay(this->_model->GetPosition(), angle, &_range);
		other->_model->IntersectRay(position, angle, &_range);
		//取得できなかった場合処理をカット
		if (_range <= 0.0f)  continue;
		//距離が最小値のものに更新
		if (_range < range) {
			range = _range;
			p_result = other->GetThisHitBox();
		}
	}

	return  p_result;
}

/**
 * @fn
 * @param (std::string tag) 引数の説明 欲しいヒットボックスのタグ
 * @return 戻り値の説明　ヒットボックスを取得返す
 * @detail 詳細な説明　外部にあるヒットボックスを取得できる
 */
HitBox* HitBox::GetHitBoxTag(std::string tag)
{
	ASSERT(Tag_Sarch(tag) && "tagが存在していない!");
	HitBox* hitbox = nullptr;
	for (auto&& other_hitbox : _HitBox_list)
	{
		if (other_hitbox->_tag != tag) continue;
		//タグ以外を弾く
		if (this == other_hitbox->GetThisHitBox()) continue;
		//自分を弾く
		hitbox = other_hitbox->GetThisHitBox();
	}

	return hitbox != nullptr ? hitbox : nullptr;
}

/**
 * @fn
 * @param (std::string tags) 引数の説明　衝突判定をしたいタグを代入する
 * @return 戻り値の説明　当たっていればTRUE　当たってなかったらFALSE
 */
bool HitBox::IsHitObjects(std::string tags) {
	ASSERT(Tag_Sarch(tags) && "tagが存在していない!");
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
 * @fn 当たり判定
 * @brief OBBを使用せず当たり判定のBOXを用いた判定
 * @param (std::string tags) 衝突判定をしたいタグを代入する
 * @return 戻り値の説明　当たっていればTRUE　当たってなかったらFALSE
 */
bool HitBox::IsHitObjectsSquare(std::string tags)
{
	bool result = false;

	HitBox* hit_object;

	float dist = FLT_MAX;

	std::vector<float> dists;

	for (auto it = _HitBox_list.begin(); it != _HitBox_list.end(); ++it)
	{
		//! 自分は飛ばして次へ
		if ((*it)->_tag == this->_tag)
			continue;

		//! 探している HitBox* がが見つかったらループを抜ける
		if ((*it)->_tag == tags)
		{
			hit_object = (*it);
			break;
		}
	}

	//! 当たり判定を行っている方のモデルの座標とサイズ
	auto a_pos   = this->_position;
	auto a_scale = this->_model->GetScale() / 2;

	//! 当たっている方の座標とサイズ
	auto b_pos   = hit_object->_position;
	auto b_scale = hit_object->_model->GetScale() / 2;

	//! aとbのボックスの当たり判定
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
 * @fn 壁ずりベクトルの取得
 * @param (is_hit_list) 当たっているヒットボックスのリストを取得
 * @param (pos) 壁ずりさせたい対象の座標
 * @param (move_dir) 壁ずりさせたい対象の向きベクトル
 * @return 戻り値の説明　壁ずりのベクトル
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
 * @fn 当たっているヒットボックスを取得
 * @return 当たっているヒットボックスをリストとして返す
 */
std::list<HitBox*> HitBox::IsHitBoxList() {
	std::list<HitBox*> HitList = HitHitBoxlist();
	return HitList;
}

/**
 * @fn 当たっているヒットボックスを取得
 * @param (tag) タグのヒットボックスを除外する
 * @return 当たっているヒットボックスをリストとして返す
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
