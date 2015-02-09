#ifndef NephilimAxTriggers_h__
#define NephilimAxTriggers_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Animation/Animation.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API AxKillTrigger : public Animation
{
public:

	bool isOver();

	float update(float delta);
};

NEPHILIM_NS_END
#endif // NephilimAxTriggers_h__