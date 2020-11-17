#include "StageManager.h"
#include "../../Stage/Stage_1/Stage.h"
#include <fstream>
#include <cstdio>

StageManager::StageManager()
{
	
}

StageManager::~StageManager()
{
	
}

bool StageManager::Initialize()
{
	FILE* fp = fopen("MapSprite/mapenglish.csv","r");

	//�}�b�v�f�[�^��ǂݍ���
	char lordchar[CHAR_MAX + 1];

	while (fgets(lordchar,sizeof lordchar -1 ,fp) !=  NULL)
	{
		mapdate.push_back(lordchar);
	}

	//�J���}��T�����ăJ���}������
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
	//�t�@�C�������
	fclose(fp);
	
	stages.emplace(FLOOR_TAG, new Floor);
	stages[FLOOR_TAG]->Initialize();
	stages[FLOOR_TAG]->SetPosition(Vector3_Zero);

	for (int z = 0; z < mapdate.size(); z++)
	{
		for (int x = 0; x < mapdate[z].size(); x++)
		{
			std::string tag = std::to_string(z) + std::to_string(x);
			switch (mapdate[z][x]) {
			case 'b':
				tag = DESTRUCTION_BLOCK_TAG + tag;
				stages.emplace(tag, new Block);
				stages[tag]->Initialize();
				break;
			case 'i':
				tag = INDESTRUCTIBIEPILLAR_TAG + tag;
				stages.emplace(tag, new Pillar);
				stages[tag]->Initialize();
				break;
			case 'o':
				tag = WALL_METAL_TAG + tag;
				stages.emplace(tag, new Metal);
				stages[tag]->Initialize();
				break;
			default:
				//�ǂ���Y�����Ȃ��Ƃ�
				//����͉������Ȃ�
				break;
			}
		}
	}
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
	// �ǂݍ��񂾍��W�f�[�^�����Ƃɕ`��
	for (int z = 0; z < mapdate.size(); z++)
	{
		for (int x = 0; x < mapdate[z].size(); x++)
		{
			std::string tag;
			switch (mapdate[z][x]) {
			case 'b':
				tag = DESTRUCTION_BLOCK_TAG + std::to_string(z) + std::to_string(x);
				stages[tag]->SetPosition(Vector3(x - 7, 0, -z + 6));
				stages[tag]->Draw3D();
				break;
			case 'i':
				tag = INDESTRUCTIBIEPILLAR_TAG + std::to_string(z) + std::to_string(x);
				stages[tag]->SetPosition(Vector3(x - 7, 0, -z + 6));
				stages[tag]->Draw3D();
				break;
			case 'o':
				tag = WALL_METAL_TAG + std::to_string(z) + std::to_string(x);
				stages[tag]->SetPosition(Vector3(x - 7, 0, -z + 6));
				stages[tag]->Draw3D();
				break;
			default:
				//�ǂ���Y�����Ȃ��Ƃ�
				//����͉������Ȃ�
				break;
			}
		}
	}

	stages[FLOOR_TAG]->Draw3D();
}
