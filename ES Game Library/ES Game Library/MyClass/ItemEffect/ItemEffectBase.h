#include"../../ESGLib.h"



class ItemEffectBase
{
public:
	ItemEffectBase();
	virtual ~ItemEffectBase();
	virtual bool Initialize(int) = 0;
	virtual int  Updata() = 0;



protected:

private:

};