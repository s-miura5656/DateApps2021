#include "HitBox.h"

//static
std::list<HitBox*> HitBox::_HitBox_list;
//デストラクタ
HitBox::~HitBox() {
	OnReMove();
}
void HitBox::Init() {
	//HitBox生成
	SetHitBox(1.f, 1.f, 1.f);
	//自分をリストに挿入
	_HitBox_list.push_back(this);

	//タグ設定
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

//ヒットボックス生成
void HitBox::SetHitBox(float width, float height, float depth) {
	//パラメータ設定
	_width = width;
	_height = height;
	_depth = depth ;
	//Model設定
	SimpleShape   shape;
	shape.Type = Shape_Box;
	shape.Width = _width;
	shape.Height = _height;
	shape.Depth = _depth;
	_model = GraphicsDevice.CreateModelFromSimpleShape(shape);
	//Material設定
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


//指定方向にRayを飛ばし衝突した指定タグのオブジェクトを親に持つHitBoxを検索し距離が最も近いHitBoxを取得
HitBox* HitBox::TypeRayRange(std::string tag, Vector3 position, Vector3 angle, float& range) {

	range = 99999.0f;
	HitBox* p_result = nullptr;

	for (auto&& other : _HitBox_list) {
		//タグが異なる場合処理をカット
		if (other->tag != tag) continue;
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
HitBox* HitBox::Get_Tag_HitBox(std::string tag)
{
	ASSERT(Tag_Sarch(tag) && "tagが存在していない!");
	HitBox* hitbox = nullptr;
	for (auto&& other_hitbox : _HitBox_list)
	{
		if (other_hitbox->tag != tag) continue;
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
	for (auto&& other : HitList) {
		if (other->tag == tags) {
			result = true;
		}
	}
	return result;
}
