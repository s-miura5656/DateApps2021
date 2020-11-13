#pragma once
#include "../../ESGLib.h"
#include"../Ui/BaseUi.h"

class ResultUi : public BaseUi
{
private:


public:
	ResultUi();
	~ResultUi();

	bool Initialize() override;
	int Update() override { return 0; }
	void Draw2D() override;
};