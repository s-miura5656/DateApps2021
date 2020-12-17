#include"RotatingFloor .h"
#include"../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Data/WordsTable.h"
#include "../../../Data/MyAlgorithm.h"

RotatingFloor::RotatingFloor(std::string tag)
{
	_model = nullptr;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_tag = tag;
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(0.5f);
    rotation = 0;
}

RotatingFloor::~RotatingFloor()
{
    _hit_box.reset();
}

bool RotatingFloor::Initialize()
{
	//Xファイルの読み込み
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/arrow_1.X"));
	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());

	_hit_box->SetHitBoxPosition(_position);

	flag = false;

    front = Vector3(0, 0, 0);
	return _model != nullptr;
}

int RotatingFloor::Update()
{
    bool isPlayerHit = PlayerHitCheck();
    
    if (isHitEnter == false && isPlayerHit == true)
    {
        isHitEnter = true;
        rotation += 90;
        rotation = AngleClamp(rotation);
    }
    
    if (isPlayerHit == false)
    {
        isHitEnter = false;
    }
    front = _model->GetFrontVector();
    orthodontics();
    return 0;
}

bool RotatingFloor::PlayerHitCheck()
{
    for (int i = 0; i < PLAYER_COUNT_MAX; i++)
    {
        std::string player_tag = PLAYER_TAG + std::to_string(i + 1);

        if (!_hit_box->Tag_Sarch(player_tag))
            continue;

        if (_hit_box->IsHitObjectsSquare(player_tag))
        {
            return true;
        }
    }

    return false;
}

void RotatingFloor::Draw3D()
{
	_model->SetPosition(_position);
	_model->SetRotation(0, rotation, 0);
	//_model->Draw();
}

void RotatingFloor::orthodontics()
{
    if (front.x >= 0.9) {
        front.x = 1.0;
        front.z = 0;
    }
    if (front.x <= -0.9) {
        front.x = -1.0;
        front.z = 0;
    }
    if (front.z == -1) {
        front.x = 0;
    }
}