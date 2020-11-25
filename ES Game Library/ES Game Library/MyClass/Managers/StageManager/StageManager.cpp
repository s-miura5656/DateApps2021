#include "StageManager.h"
#include "../../Stage/Stage_1/Stage.h"
#include <fstream>
#include <cstdio>
#include "../../Data/IData.h"

StageManager::StageManager()
{
	
}

StageManager::~StageManager()
{
	//std::string tag = DESTRUCTION_BLOCK_TAG + std::to_string(blockpos[a].z) + std::to_string(blockpos[a].x);
	//stages.erase(tag,Block);
}

bool StageManager::Initialize()
{
	random_item[0] = POWOR_ITEM_TAG;
	random_item[1] = SPEED_ITEM_TAG;
	random_item[2] = HITPOINT_ITEM_TAG;

	//配列の添え字でタグを呼べる
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
			switch (mapdate[z][x]) {
			case 'b':
				tag = DESTRUCTION_BLOCK_TAG + tag;
				stages.emplace(tag, new Block(tag));
				stages[tag]->SetPosition(Vector3(x, 0, -z));
				stages[tag]->SetRotation(Vector3_Zero);
				stages[tag]->Initialize();
				tags.push_back(tag);
				flag.push_back(false);
				imap_data->SetPosition(Vector3(x, 0, -z));
				break;
			case 'i':
				tag = INDESTRUCTIBIEPILLAR_TAG + tag;
				stages.emplace(tag, new Pillar(tag));
				stages[tag]->SetPosition(Vector3(x, 0, -z));
				stages[tag]->SetRotation(Vector3_Zero);
				stages[tag]->Initialize();
				tags.push_back(tag);
				imap_data->SetPosition(Vector3(x, 0, -z));
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
				imap_data->SetPosition(Vector3(x, 0, -z));

				break;
			case ' ':
				imap_data->SetPosition(Vector3(x, 0, -z));

				break;
			default:
				//どれも該当しないとき
				//今回は何もしない
				break;
			}
		}
	}

	delete imap_data;
	delete iplayer_data;
	delete itemcounter;

	int size = stages.size();
	return true;
}

int StageManager::Update()
{
	auto   it  = stages.begin();
	while (it != stages.end())
	{
		if ((*it).second->Update() == 1) {
			ItemCounter* itemcounter = new ItemCounter;
			itemcounter->SetItem(random_item[rand() % 3], it->second->GetPosition());
			stages.erase(it++);
		}
		else {
			++it;
		}
	}

	return 0;
}

void StageManager::Draw2D()
{
	
}

void StageManager::Draw3D()
{
//読み込んだブロックの数だけ描画する
	auto   it = stages.begin();
	while (it != stages.end())
	{
		it->second->Draw3D();

		++it;
	}
	/*for (const auto& tag : tags)
	{
		stages[tag]->Draw3D();
	}*/
	stages[FLOOR_TAG]->Draw3D();
}
