#include"Warp.h"
#include "../../../Data/WordsTable.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Data/IData.h"
#include "../../../Players/PlayerBase.h"
Warp::Warp(std::string tag)
{
	_model = nullptr;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(tag);
	_hit_box->SetHitBox(1, 1, 1);
}

Warp::~Warp()
{
	_hit_box.reset();
}

bool Warp::Initialize()
{
	//Xファイルの読み込み
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/warp.X"));
	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());

	_hit_box->SetHitBoxPosition(_position);

	return _model != nullptr;
}
int Warp::Update()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string player_tag = PLAYER_TAG + std::to_string(i + 1);

		if (!_hit_box->Tag_Sarch(player_tag))
		{
			continue;
		}

		if (_hit_box->IsHitObjectsSquare(player_tag))
		{
			std::unique_ptr<IMapData> map_data = std::make_unique<IMapData>();
			std::vector<Vector3> _other_position;
			auto other_position = map_data->GetWarp();
			for (int i = 0; i < other_position.size(); i++)
			{
				if (other_position[i] == _position)
				{
					continue;
				}
				else
				{
					_other_position.push_back(other_position[i]);
				}
			}
			int random_index = MathHelper_Random(_other_position.size() - 1);
			_hit_box->GetHitBoxTag(player_tag)->GetPlayerBase()->Warp(_other_position[random_index]);
			return 0;
		}
	}

	return 0;
}

void Warp::Draw3D()
{
	_hit_box->SetHitBoxPosition(_position);
	_model->SetPosition(_position);
	_model->Draw();
}
