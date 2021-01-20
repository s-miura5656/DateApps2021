#include "StageManager.h"
#include <fstream>
#include <cstdio>
#include "../../Data/IData.h"
#include "../../Data/WordsTable.h"
#include "../../Data/StructList.h"
#include "../ResouceManager/ResouceManager.h"

StageManager::StageManager()
{
}

StageManager::~StageManager()
{
	for (int i = _stages.size() - 1; i >= 0; --i)
	{
		delete _stages[i];
	}
}

bool StageManager::Initialize()
{
	MediaManager.Attach(GraphicsDevice);
	_bg_movie  = ResouceManager::Instance().LordMediaFile(_T("MapSprite/bg.wmv"));
	_respawn   = ResouceManager::Instance().LoadModelFile(_T("MapSprite/Respawn/Respawn.X"));

	_bg_movie->Play();

	FILE* fp = fopen("MapSprite/Stage/map_A.csv", "r");

	//マップデータを読み込む
	char lordchar[CHAR_MAX + 1];

	while (fgets(lordchar, sizeof lordchar - 1, fp) != NULL)
	{
		if (lordchar[strlen(lordchar) - 1] == '\n')
			lordchar[strlen(lordchar) - 1] = '\0';
		_mapdate.push_back(lordchar);
	}
	//カンマを探索してカンマを消す
	for (int z = 0; z < _mapdate.size(); z++)
	{
		for (int x = 0; x < _mapdate[z].size(); x++)
		{
			if (_mapdate[z][x] == ',')
			{
				_mapdate[z].erase(_mapdate[z].begin() + x);
			}
		}
	}

	//!外壁、破壊不可ブロック、破壊可能ブロック以外の座標を
	for (int z = 0; z < _mapdate.size(); z++)
	{
		for (int x = 0; x < _mapdate[z].size(); x++)
		{
			if (_mapdate[z][x] == '?')
			{
				_random_block_position.push_back(Vector3(x, 0, -z));
			}
		}
	}
	//ファイルを閉じる
	fclose(fp);

	IPrayerData* iplayer_data = new IPrayerData;
	int player_num = 1;

	IMapData* imap_data = new IMapData;

	_count = 0;
	int	respawn_player_tag = 1;
	for (int z = 0; z < _mapdate.size(); z++)
	{
		for (int x = 0; x < _mapdate[z].size(); x++)
		{
			std::string tag = std::to_string(_count);
			switch (_mapdate[z][x]) {
			case 'b':
				tag = DESTRUCTION_BLOCK_TAG + tag;
				_stages.push_back(new Block(tag, NULL_ITEM_TAG));
				_stages[_count]->SetPosition(Vector3(x, 0, -z));
				_stages[_count]->Initialize();
				_count++;
				break;
			case 'p':
				tag = PLAYER_TAG + std::to_string(player_num);
				iplayer_data->SetPosition(tag, Vector3(x, 0, -z));
				player_num++;
				break;
			case 'r':
				tag = PLAYER_TAG + std::to_string(respawn_player_tag);
				imap_data->SetRespawnPosition(tag,Vector3(x,0,-z));
				_respawn->SetRotation(Vector3_Zero);
				_respawn->SetScale(1.0f);
				respawn_player_tag++;
				break;
			}
		}
	}

	imap_data->SetData(_mapdate);

	_stages.push_back(new Indestructible);
	_stages[_stages.size() - 1]->Initialize();
	_stages[_stages.size() - 1]->SetPosition(Vector3(7, 0, -6));

	delete imap_data;
	delete iplayer_data;

	int size = _stages.size();
	_random_item[0] = POWOR_ITEM_TAG;
	_random_item[1] = SPEED_ITEM_TAG;
	_random_item[2] = HITPOINT_ITEM_TAG;
	return true;
}

int StageManager::Update()
{
	if(_bg_movie->IsComplete())
	_bg_movie->Replay();
	_random_fall_time++;
	//TODO:降ってくる頻度は調整する
	if (_random_fall_time >= FALL_BLOCK_INTERVAL)
	{
		IMapData* imap_data = new IMapData;
		_mapdate = imap_data->GetData();

		RandomBlockSet();
		_random_fall_time = 0;
		delete imap_data;
	}

	for (int i = 0; i < _stages.size(); i++)
	{
		//!ブロックが破壊されたとき
		if (_stages[i]->Update() == 1)
		{
			_stages.erase(_stages.begin() + i);
		}
	}
	return 0;
}

void StageManager::Draw2D()
{
	SpriteBatch.Draw(*_bg_movie, Vector3(0, 0, 10000),1.0f);
}

void StageManager::Draw3D()
{
	//読み込んだブロックの数だけ描画する
	for (int i = 0; i < _stages.size(); ++i)
	{
		_stages[i]->Draw3D();
	}
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);
		Material mat;
		mat.Diffuse = Color(1.0f, 1.0f, 1.0f);
		mat.Ambient = Color(1.0f, 1.0f, 1.0f);
		mat.Specular = Color(1.0f, 1.0f, 1.0f);
		_respawn->SetMaterial(mat);
		_rotation += 3;
		if (_rotation >= 360)
			_rotation = 0;
		_respawn->SetRotation(Vector3(0, _rotation, 0));
		_respawn->SetPosition(IMapData::GetRespawnPosition(tag));
		_respawn->Draw();
	}
}

void StageManager::DrawAlpha3D()
{
	for (int i = 0; i < _stages.size(); ++i)
	{
		_stages[i]->DrawAlpha3D();
	}
}
/**
 * @fn ブロックをランダムな座標に置く
 */
void StageManager::RandomBlockSet()
{
	std::vector<Vector3>random_block_pos;
	for (int i = 0; i < _random_block_position.size(); i++)
	{
		int x = _random_block_position[i].x;
		int z = -_random_block_position[i].z;
		if (_mapdate[z][x] == '?')
		{
			random_block_pos.push_back(_random_block_position[i]);
		}
	}
	if (random_block_pos.size() == 0)
	{
		return;
	}
	//!保存した座標をシャッフルする
	for (int i = 0; i < random_block_pos.size(); ++i)
	{
		const auto random_index = MathHelper_Random(random_block_pos.size() - 1);
		const auto work = random_block_pos.at(random_index);
		random_block_pos.at(random_index) = random_block_pos.at(i);
		random_block_pos.at(i) = work;
	}

	for (int i = 0; i < MathHelper_Random(1,2); i++) 
	{
		random_block_pos[i].y = 10;
		ItemCounter::SetItem(SPEED_ITEM_TAG, random_block_pos[i], 0);
		if (random_block_pos.size() == 1)
			return;
	}
}