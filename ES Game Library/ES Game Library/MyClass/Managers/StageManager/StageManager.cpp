#include "StageManager.h"
#include "../../Stage/Stage_1/Stage.h"
#include <fstream>
#include <cstdio>

StageManager::StageManager()
{
	block = nullptr;
	pillar = nullptr;
	metal = nullptr;
	floor = nullptr;
}

StageManager::~StageManager()
{
	delete floor;
	delete metal;
	delete pillar;
	delete block;
}

bool StageManager::Initialize()
{
	block = new Block();
	if (!(block->Initialize()))
	{
		return false;
	}
	pillar = new Pillar();
	if (!(pillar->Initialize()))
	{
		return false;
	}
	metal = new Metal();
	if (!(metal->Initialize()))
	{
		return false;
	}
	floor = new Floor();
	if (!(floor->Initialize()))
	{
		return false;
	}
	// CSV�ǂݍ���
	//std::ifstream infile("MapSprite/mapenglish.csv");
	//std::string line;
	//int z = 0, x = 0;
	//while (getline(infile, line))
	//{
	//	for (int i = 0; i < line.length(); ++i)
	//	{
	//		if (line[i] != ',') {
	//			xz[z][x] = line[i];
	//			x++;
	//			if (x >= _countof(xz[z])) {
	//				++z;
	//				x = 0;
	//			}
	//		}
	//	}
	//}

	FILE* fp = fopen("MapSprite/mapenglish.csv","r");
	//�}�b�v�f�[�^��ǂݍ���
	char lordchar[CHAR_MAX + 1];

	while (fgets(lordchar,sizeof lordchar -1 ,fp) !=  NULL)
	{
		mapdate.push_back(lordchar);
	}

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

	floor->SetPosition(Vector3(0, 0, 0));
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
			switch (mapdate[z][x]) {
			case 'b':
				block->SetPosition(Vector3(x - 7, 0, -z + 6));
				block->Draw3D();
				break;
			case 'i':
				pillar->SetPosition(Vector3(x - 7, 0, -z + 6));
				pillar->Draw3D();
				break;
			case 'o':
				metal->SetPosition(Vector3(x - 7, 0, -z + 6));
				metal->Draw3D();
				break;
			default:
				//�ǂ���Y�����Ȃ��Ƃ�
				//����͉������Ȃ�
				break;
			}
		}
	}
	floor->Draw3D();
}
