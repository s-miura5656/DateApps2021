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

	FILE* fp = fopen("MapSprite/map.csv","r");

	//マップデータを読み込む
	char lordchar[CHAR_MAX + 1];

	while (fgets(lordchar,sizeof lordchar -1 ,fp) !=  NULL)
	{
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
	stages[stages.size() - 1]->SetPosition(Vector3(7,0,-6));

	delete imap_data;
	delete iplayer_data;

	int size = stages.size();

	return true;
}

int StageManager::Update()
{
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
