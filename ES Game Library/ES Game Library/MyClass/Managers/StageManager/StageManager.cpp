#include "StageManager.h"
#include "../../Stage/Stage_1/Stage.h"
#include <fstream>
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
	// CSV読み込み
	std::ifstream infile("MapSprite/map.csv");
	std::string line;
	for (int z = 0; z < _countof(xz); ++z) {
		for (int x = 0; x < _countof(xz[z]); ++x) {
			infile >> xz[z][x];
			if (x != _countof(xz[z]) - 1) {
				infile >> comma;
			}
			else {
				getline(infile, line);
			}
		}
	}
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
	// 読み込んだ座標データをもとに描画
	for (int z = 0; z < _countof(xz); z++)
	{
		for (int x = 0; x < _countof(xz[0]); x++)
		{
			switch (xz[z][x]) {
			case 0:
				break;
			case 1:
				block->SetPosition(Vector3(x - 7, 0, -z + 6));
				block->Draw3D();
				break;
			case 2:
				pillar->SetPosition(Vector3(x - 7, 0, -z + 6));
				pillar->Draw3D();
				break;
			case 3:
				metal->SetPosition(Vector3(x - 7, 0, -z + 6));
				metal->Draw3D();
				break;
			default:
				//どれも該当しないとき
				//今回は何もしない
				break;
			}
		}
	}
	floor->Draw3D();
}
