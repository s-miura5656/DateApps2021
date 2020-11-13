#pragma once
#include "../../ESGLib.h"
#include"../Ui/BaseUi.h"

class TitleUi : public BaseUi
{
private:
	TitleUi(const TitleUi&) = delete;
	void operator=(const TitleUi&) = delete;



public:
	TitleUi();
	~TitleUi();

	bool Initialize() override;
	int Update() override { return 0; }
	void Draw2D() override;
};