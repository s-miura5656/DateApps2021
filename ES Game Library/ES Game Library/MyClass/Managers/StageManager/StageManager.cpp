#include "StageManager.h"
#include <fstream>
#include <cstdio>
#include "../../Data/IData.h"
#include "../../Data/WordsTable.h"
#include "../../Data/StructList.h"
#include"../ResouceManager/ResouceManager.h"
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
	_bg_sprite = ResouceManager::Instance().LordSpriteFile(_T("MapSprite/BG.png"));

	FILE* fp = fopen("MapSprite/map.csv", "r");

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
	//ファイルを閉じる
	fclose(fp);

	IPrayerData* iplayer_data = new IPrayerData;
	int player_num = 1;

	IMapData* imap_data = new IMapData;
	std::vector<int> warpdata;

	_count = 0;
	for (int z = 0; z < _mapdate.size(); z++)
	{
		for (int x = 0; x < _mapdate[z].size(); x++)
		{
			std::string tag = std::to_string(_count);
			switch (_mapdate[z][x]) {
			case 'b':
				tag = DESTRUCTION_BLOCK_TAG + tag;
				_stages.push_back(new Block(tag, NULL_ITEM));
				_stages[_count]->SetPosition(Vector3(x, 0, -z));
				_stages[_count]->Initialize();
				_count++;
				break;
			case 's':
				tag = DESTRUCTION_BLOCK_TAG + tag;
				_stages.push_back(new Block(tag, POWOR_ITEM_TAG));
				_stages[_count]->SetPosition(Vector3(x, 0, -z));
				_stages[_count]->Initialize();
				_count++;
				_mapdate[z][x] = 'b';
				break;
			case 'p':
				tag = PLAYER_TAG + std::to_string(player_num);
				iplayer_data->SetPosition(tag, Vector3(x, 0, -z));
				player_num++;
				break;
			case 'r':
				tag = ROTATION_FLOOR_TAG + tag;
				_stages.push_back(new RotatingFloor(tag));
				_stages[_count]->SetPosition(Vector3(x, 0.1, -z));
				_stages[_count]->Initialize();
				_count++;
				break;
			case 'o':
				tag = WARP_TAG + tag;
				_stages.push_back(new Warp(tag));
				_stages[_count]->SetPosition(Vector3(x, 0.1, -z));
				_stages[_count]->Initialize();
				warpdata.push_back(_count);
				_count++;
				break;
			}
		}
	}

	imap_data->SetData(_mapdate);
	imap_data->SetWarp(warpdata);

	_stages.push_back(new Indestructible);
	_stages[_stages.size() - 1]->Initialize();
	_stages[_stages.size() - 1]->SetPosition(Vector3(7, 0, -6));

	delete imap_data;
	delete iplayer_data;

	int size = _stages.size();
	return true;
}

int StageManager::Update()
{
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
	SpriteBatch.Draw(*_bg_sprite, Vector3(0, 0, 10000), 1.0f);
}

void StageManager::Draw3D()
{
	//読み込んだブロックの数だけ描画する
	for (int i = 0; i < _stages.size(); ++i)
	{
		_stages[i]->Draw3D();
	}
}

void StageManager::DrawAlpha3D()
{
	for (int i = 0; i < _stages.size(); ++i)
	{
		_stages[i]->DrawAlpha3D();
	}
}