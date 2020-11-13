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
	stages.emplace("FieldBase", new Floor);
	stages["FieldBase"]->Initialize();
	stages["FieldBase"]->SetPosition(Vector3_Zero);

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
	
	for (int z = 0; z < mapdate.size(); z++)
	{
		for (int x = 0; x < mapdate[z].size(); x++)
		{
			switch (mapdate[z][x]) {
			case 'b':
				stages.emplace("Block" + std::to_string(z) + std::to_string(x), new Block);
				stages["Block" + std::to_string(z) + std::to_string(x)]->Initialize();
				break;
			case 'i':
				stages.emplace("Pillar" + std::to_string(z) + std::to_string(x), new Pillar);
				stages["Pillar" + std::to_string(z) + std::to_string(x)]->Initialize();
				break;
			case 'o':
				stages.emplace("Metal" + std::to_string(z) + std::to_string(x), new Metal);
				stages["Metal" + std::to_string(z) + std::to_string(x)]->Initialize();
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
			switch (mapdate[z][x]) {
			case 'b':
				stages["Block" + std::to_string(z) + std::to_string(x)]->SetPosition(Vector3(x - 7, 0, -z + 6));
				stages["Block" + std::to_string(z) + std::to_string(x)]->Draw3D();
				break;
			case 'i':
				stages["Pillar" + std::to_string(z) + std::to_string(x)]->SetPosition(Vector3(x - 7, 0, -z + 6));
				stages["Pillar" + std::to_string(z) + std::to_string(x)]->Draw3D();
				break;
			case 'o':
				stages["Metal" + std::to_string(z) + std::to_string(x)]->SetPosition(Vector3(x - 7, 0, -z + 6));
				stages["Metal" + std::to_string(z) + std::to_string(x)]->Draw3D();
				break;
			default:
				//�ǂ���Y�����Ȃ��Ƃ�
				//����͉������Ȃ�
				break;
			}
		}
	}

	stages["FieldBase"]->Draw3D();
}
