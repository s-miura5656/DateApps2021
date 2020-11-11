#pragma once
#include "../../ESGLib.h"
#include <functional>

class HitBox {
public:
	//デストラクタ
	virtual HitBox::~HitBox();

	//初期化
	virtual void HitBox::Init();

	//描画
	virtual void HitBox::Draw3D();
	virtual void HitBox::DrawAlpha3D();

	//パラメータを設定
	virtual void HitBox::SetHitBox(float width, float height, float depth);

	//消去時に呼ばれる処理
	void HitBox::OnReMove();

	void SetHitBoxScale(float sca);	
	void SetHitBoxScale(Vector3 sca);

	void SetHitBoxPosition(Vector3 pos);

	//自身を返す
	HitBox* HitBox::GetThisHitBox() { return this; };

	//衝突しているHitBoxのリストを取得
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
	//全てのHitBoxを格納しておくリスト
	static std::list<HitBox*> _HitBox_list;

	//判定用のモデル
	MODEL _model = nullptr;

	//パラメータ
	float _width = 1.0f;
	float _height = 1.0f;
	float _depth = 1.0f;

	Vector3 position;
	Vector3    scale;

	Vector3 color = Vector3(1.0f, 0.0f, 0.0f);

	//衝突判定関数
	bool HitBox::IsHit(HitBox* other);

protected:
	
};