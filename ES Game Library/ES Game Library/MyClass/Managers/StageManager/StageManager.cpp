#include "StageManager.h"
#include "../../Stage/Stage_1/Stage.h"
#include <fstream>
#include <cstdio>
#include "../../Data/IData.h"
#include "../../Data/StructList.h"

StageManager::StageManager()
{
	
}

StageManager::~StageManager()
{
	
}

bool StageManager::Initialize()
{
	//配列の添え字でタグを呼べる
	string random_item[3] = { POWOR_ITEM_TAG ,SPEED_ITEM_TAG ,HITPOINT_ITEM_TAG };
	srand((unsigned int)time(NULL));
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
	
	stages.emplace(FLOOR_TAG, new Floor);
	stages[FLOOR_TAG]->Initialize();
	stages[FLOOR_TAG]->SetPosition(Vector3(7, 0, -6));
	stages[FLOOR_TAG]->SetRotation(Vector3_Zero);

	ItemCounter* itemcounter = new ItemCounter;
	IPrayerData* iplayer_data = new IPrayerData;
	int player_num = 1;
	std::vector<Vector3> pos;

	IMapData* imap_data = new IMapData;
	

	for (int z = 0; z < mapdate.size(); z++)
	{
		for (int x = 0; x < mapdate[z].size(); x++)
		{
			std::string tag = std::to_string(z) + std::to_string(x);
			MapData data;
			switch (mapdate[z][x]) {
			case 'b':
				tag = DESTRUCTION_BLOCK_TAG + tag;
				stages.emplace(tag, new Block);
				stages[tag]->SetPosition(Vector3(x, 0, -z));
				stages[tag]->SetRotation(Vector3_Zero);
				stages[tag]->Initialize();
				tags.push_back(tag);
				data.position = Vector3(x, 0, -z);
				imap_data->SetData(data);
				break;
			case 'i':
				tag = INDESTRUCTIBIEPILLAR_TAG + tag;
				stages.emplace(tag, new Pillar(tag));
				stages[tag]->SetPosition(Vector3(x, 0, -z));
				stages[tag]->SetRotation(Vector3_Zero);
				stages[tag]->Initialize();
				tags.push_back(tag);
				data.position = Vector3(x, 0, -z);
				data.move_flag = true;
				imap_data->SetData(data);
				break;
			case 'o':
				tag = WALL_METAL_TAG + tag;
				stages.emplace(tag, new Metal(tag));
				stages[tag]->SetPosition(Vector3(x, 0, -z));
				if (z == 0) {
					stages[tag]->SetRotation(Vector3(0, 270, 0));
				}
				else if (x == 0) {
					stages[tag]->SetRotation(Vector3(0, 180, 0));
				}
				else if (z == mapdate.size() - 1) {
					stages[tag]->SetRotation(Vector3(0, 90, 0));
				}
				else {
					stages[tag]->SetRotation(Vector3(0, 0, 0));
				}
				stages[tag]->Initialize();
				pos.push_back(Vector3(x, 0, -z));
				tags.push_back(tag);
				break;
			case 'c':
				tag = WALL_METAL_TAG + tag;
				stages.emplace(tag, new WallCorner);
				stages[tag]->SetPosition(Vector3(x, -0.5, -z));
				stages[tag]->SetRotation(Vector3_Zero);
				if (z == 0) {
					stages[tag]->SetRotation(Vector3(0, 270, 0));
					if (x == mapdate.size() + 1) {
						stages[tag]->SetRotation(Vector3(0, 0, 0));
					}
				}
				if (z == mapdate.size() - 1) {
					stages[tag]->SetRotation(Vector3(0, 180, 0));
					if (x == mapdate.size() + 1) {
						stages[tag]->SetRotation(Vector3(0, 90, 0));
					}
				}
				stages[tag]->Initialize();
				tags.push_back(tag);
				break;
			case 'p':
				tag = PLAYER_TAG + std::to_string(player_num);
				iplayer_data->SetPosition(tag, Vector3(x, 0, -z));
				player_num++;
				data.position = Vector3(x, 0, -z);
				imap_data->SetData(data);
				break;
			case ' ':
				data.position = Vector3(x, 0, -z);
				imap_data->SetData(data);
				break;
			default:
				//どれも該当しないとき
				//今回は何もしない
				break;
			}
		}
	}

	auto a = imap_data->GetData();

	delete imap_data;
	delete iplayer_data;
	delete itemcounter;

	int size = stages.size();
	return true;
}

int StageManager::Update()
{
	return 0;
}

void StageManager::Draw2D()
{
	
}

void StageManager::Draw3D()
{
//読み込んだブロックの数だけ描画する
	for (const auto& tag : tags)
	{
		stages[tag]->Draw3D();
	}
	stages[FLOOR_TAG]->Draw3D();
}
