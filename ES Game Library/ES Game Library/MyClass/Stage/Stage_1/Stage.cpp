#include"Stage.h"
#include <fstream>
/*
* @fn �v���C���[�̏�����
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
bool Stage::Initialize()
{
//	/**
//* @brief �}�b�v�̃}�e���A���̏����ݒ�
//*/
//	material.Diffuse = Color(1.0f, 1.0f, 1.0f);
//	material.Ambient = Color(1.0f, 1.0f, 1.0f);
//	material.Specular = Color(1.0f, 1.0f, 1.0f);
//	material.Power = 0.0f;
//
//	/**
//* @brief �u���b�N�̏����ݒ�
//*/
//	block = GraphicsDevice.CreateModelFromFile(_T("MapSprite/block.X"));
//	block->SetScale(scale);
//	block->SetMaterial(material);
//
//	/**
//* @brief �j��ł��Ȃ��u���b�N�̏����ݒ�
//*/
//	pillar = GraphicsDevice.CreateModelFromFile(_T("MapSprite/Pillar.X"));
//	pillar->SetScale(scale * 0.9f);
//	pillar->SetMaterial(material);
//
//	/**
//* @brief map�̏����ݒ�
//*/
//	map = GraphicsDevice.CreateModelFromFile(_T("MapSprite/ground.X"));
//	map->SetScale(scale);
//	map->SetMaterial(material);
//	map->SetPosition(0, 0, 0);
//
//	/**
//* @brief �O�ǂ̏����ݒ�
//*/
//	metal = GraphicsDevice.CreateModelFromFile(_T("MapSprite/metal.X"));
//	metal->SetScale(scale);
//	metal->SetMaterial(material);
//
//	/**
//* @brief �t�@�C���ǂݍ���
//*/
//	std::ifstream infile("MapSprite/map.csv");
//	std::string line;
//	for (int z = 0; z < 13; ++z) {
//		for (int x = 0; x < _countof(xz[z]); ++x) {
//			infile >> xz[z][x];
//			if (x != _countof(xz[z]) - 1) {
//				infile >> comma;
//			}
//			else {
//				getline(infile, line);
//			}
//		}
//	}
//	map_position = map->GetPosition();



	return true;
}

/*
* @fn �v���C���[�`��
* @param�@�Ȃ�
* @return�@�Ȃ�
*/
//void Stage::Draw3D()
//{
/**
* @brief �u���b�N�̔z�u
*/
	/*for (int z = 0; z < 13; z++)
	{
		for (int x = 0; x < 15; x++)
		{
			switch (xz[z][x]) {
			case 0:
				break;
			case 1:
				block->SetPosition(x, 1, z);
				block->SetRotation(0, 0, 0);
				block->Draw();

				break;
			case 2:
				pillar->SetPosition(x - 7.f, 1, z - 6.f);
				pillar->SetRotation(0, 0, 0);
				pillar->Draw();
				break;
			case 3:
				metal->SetPosition(x - 7.f, 1, z - 6.f);
				metal->SetRotation(0, 0, 0);
				metal->Draw();
				break;
			default:
				�ǂ���Y�����Ȃ��Ƃ�
				����͉������Ȃ�
				break;
			}
		}
	}
	map->Draw();*/
//}

