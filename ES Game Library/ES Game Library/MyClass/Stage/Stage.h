#pragma once

#include "../ESGLib.h"

class Stage {
public:
    void Initialize();
    void Draw();
	Vector3 map_position;
private:
	Material material;
	MODEL block;//���Ȃ�
	MODEL pillar;//����
	MODEL map;//��
	const float scale = 0.0254f;
	int xz[15][19];//�t�@�C���̓ǂݍ���
	char comma;//�J���}�ǂݍ���
};