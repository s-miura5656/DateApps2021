#include"../ItemEffectBase.h"

class PlayerSpeedUp : public ItemEffectBase
{
public:
	bool Initialize(int time) override;
	int  Updata() override;
private:

};