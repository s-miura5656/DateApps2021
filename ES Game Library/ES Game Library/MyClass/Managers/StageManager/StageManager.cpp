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
	for (int i = stages.size() - 1; i >= 0; --i)
	{
		delete stages[i];
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
		mapdate.push_back(lordchar);
	}
	//カンマを探索してカンマを消す
	for (int z = 0; z < mapdate.size(); z++)
	{
		for (int x = 0; x < mapdate[z].size(); x++)
		{
			if (mapdate[z][x] == ',')
			{
				mapdate[z].erase(mapdate[z].begin() + x);
			}
		}
	}
	//ファイルを閉じる
	fclose(fp);

	IPrayerData* iplayer_data = new IPrayerData;
	int player_num = 1;

	IMapData* imap_data = new IMapData;
	imap_data->SetData(mapdate);

	std::vector<int> warpdata;
	_count = 0;
	for (int z = 0; z < mapdate.size(); z++)
	{
		for (int x = 0; x < mapdate[z].size(); x++)
		{
			std::string tag = std::to_string(_count);
			switch (mapdate[z][x]) {
			case 'b':
				tag = DESTRUCTION_BLOCK_TAG + tag;
				stages.push_back(new Block(tag));
				stages[_count]->SetPosition(Vector3(x, 0, -z));
				stages[_count]->Initialize();
				_count++;
				break;
			case 'p':
				tag = PLAYER_TAG + std::to_string(player_num);
				iplayer_data->SetPosition(tag, Vector3(x, 0, -z));
				player_num++;
				break;
			case 'r':
				tag = ROTATION_FLOOR_TAG + tag;
				stages.push_back(new RotatingFloor(tag));
				stages[_count]->SetPosition(Vector3(x, 0.1, -z));
				stages[_count]->Initialize();
				_count++;
				break;
			case 'o':
				tag = WARP_TAG + tag;
				stages.push_back(new Warp(tag));
				stages[_count]->SetPosition(Vector3(x, 0.1, -z));
				stages[_count]->Initialize();
				warpdata.push_back(_count);
				_count++;
				break;
			}
		}
	}

	imap_data->SetWarp(warpdata);

	stages.push_back(new Indestructible);
	stages[stages.size() - 1]->Initialize();
	stages[stages.size() - 1]->SetPosition(Vector3(7, 0, -6));

	delete imap_data;
	delete iplayer_data;

	int size = stages.size();

	//!変数初期化
	_fall_block_count = 10;
	_block_count = 80;
	_fall_interval = 220;
	_random_fall_time = 0;
	return true;
}

int StageManager::Update()
{
	IMapData* imap_data = new IMapData;

	//TODO:ブロックの数が80個以下の場合ランダムな座標を決めるタイマーを起動:エラーで落ちないために103個以下で止める
	if (stages.size() - 1 <= _block_count)
	{
		_random_fall_time++;
	}

	int rand_block_count = 0;

	//TODO:降ってくる頻度は調整する
	if (_random_fall_time >= _fall_interval)
	{
		mapdate = imap_data->GetData();
		RandomBlockSet();
		_random_fall_time = 0;
	}

	delete imap_data;

	for (int i = 0; i < stages.size(); i++)
	{
		if (stages[i]->Update() == 1)
		{
			const string random_item[3] = { POWOR_ITEM_TAG ,SPEED_ITEM_TAG ,HITPOINT_ITEM_TAG };
			/*ItemCounter* itemcounter = new ItemCounter;
			itemcounter->SetItem(random_item[MathHelper_Random(0,2)],stages[i]->GetPosition());*/
			stages.erase(stages.begin() + i);
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
	for (int i = 0; i < stages.size(); ++i)
	{
		stages[i]->Draw3D();
	}
}

void StageManager::DrawAlpha3D()
{
	for (int i = 0; i < stages.size(); ++i)
	{
		stages[i]->DrawAlpha3D();
	}
}
/**
 * @fn ブロックをランダムな座標に置く
 * @return trueだったらブロックが置かれる
 */
void StageManager::RandomBlockSet()
{
	std::vector<Vector3> random_block_pos;
	for (int z = 0; z < mapdate.size(); z++)
	{
		for (int x = 0; x < mapdate[z].size(); x++)
		{
			if (mapdate[z][x] != 'w' && mapdate[z][x] != 'i')
			{
				random_block_pos.push_back(Vector3(x, 0, -z));
			}
		}
	}
	for (auto&& stagepos : stages)
	{
		for (int i = 0; i < random_block_pos.size(); i++)
		{
			if (stagepos->GetPosition().x == random_block_pos[i].x && stagepos->GetPosition().z == random_block_pos[i].z)
			{
				random_block_pos.erase(random_block_pos.begin() + i);
			}
		}
	}
	int num[108] = {};
	for (int i = 0; i < random_block_pos.size(); i++)
	{
		num[i] = i;
	}
	for (int i = 0; i < random_block_pos.size(); i++)
	{
		int random = MathHelper_Random(0, random_block_pos.size());
		int work = num[i];
		num[i] = num[random];
		num[random] = work;
	}
	//TODO:ランダムで増えるブロックの個数は調整する
	for (int i = 0; i < _fall_block_count; i++)
	{
		std::string blocktag = DESTRUCTION_BLOCK_TAG + std::to_string(random_block_pos[num[i]].x) + std::to_string(random_block_pos[num[i]].z);
		stages.push_back(new Block(blocktag));
		random_block_pos[num[i]].y = MathHelper_Random(5, 10);
		stages[stages.size() - 1]->SetPosition(random_block_pos[num[i]]);
		stages[stages.size() - 1]->Initialize();
	}
}