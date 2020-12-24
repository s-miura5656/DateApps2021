#include "Blinking.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Data/IData.h"
#include "../../../Data/WordsTable.h"
#include "../../../Managers/SceneManager/SceneManager.h"
#include "../../../ParticleSystem/Particle.h"

Blinking::Blinking()
{
	_model  = nullptr;
}

Blinking::~Blinking()
{

}

bool Blinking::Initialize(Vector3 pos)
{
	//!Xファイルの読み込み
	_model  = ResouceManager::Instance().LoadModelFile(_T("MapSprite/blinking.X"));

	//!スケールの設定
	_scale = 1.0f;
	_model->SetScale(_scale);

	//!ポジションを降ってくるブロックと同じに設定する
	_position = pos;

	//!マテリアルの設定
	Material mat;
	mat.Diffuse  = Color(0.5f, 0.5f, 0.5f);
	mat.Ambient  = Color(1.0f, 1.0f, 1.0f);
	mat.Specular = Color(0.5f, 0.5f, 0.5f);
	_model->SetMaterial(mat);

	return _model != nullptr;
}
int Blinking::Update()
{
	_position.y = 0.1;

	return 0;
}

void Blinking::Draw3D()
{
	_model->SetPosition(_position);
	_model->SetRotation(0, 0, 0);
	_model->Draw();
}