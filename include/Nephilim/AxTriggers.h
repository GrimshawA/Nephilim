#ifndef NephilimAxTriggers_h__
#define NephilimAxTriggers_h__

#include "Platform.h"
#include "AxBase.h"

NEPHILIM_NS_BEGIN

class NEPHILIM_API AxKillTrigger : public AxBase
{
public:

	float update(float delta);

};

NEPHILIM_NS_END
#endif // NephilimAxTriggers_h__