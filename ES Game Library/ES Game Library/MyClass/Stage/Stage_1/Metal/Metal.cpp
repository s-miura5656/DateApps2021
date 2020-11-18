#include"Metal.h"

Metal::Metal(std::string tag)
{
	_model = nullptr;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_tag = tag;
	_hit_box->Settags(tag);
	_hit_box->SetHitBoxScale(1.1f);
}

Metal::~Metal()
{

}

bool Metal::Initialize()
{
	//Xファイルの読み込み
	_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/metal.X"));
	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());
	
	_hit_box->SetHitBoxPosition(_position);

	return _model != nullptr;
}