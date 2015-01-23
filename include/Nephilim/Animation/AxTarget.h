#ifndef NephilimAxTarget_h__
#define NephilimAxTarget_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Vector.h>

NEPHILIM_NS_BEGIN

/**
	\ingroup Animation
	\class AxTarget
	\brief Base class for animation targets
*/
class NEPHILIM_API AxTarget
{
public:

	virtual vec2 axGetPosition2D()
	{
		return vec2();
	}

	virtual void axSetPosition2D(vec2 position)
	{

	}

	virtual void axSetAlpha(float alpha)
	{

	}

	virtual float axGetAlpha()
	{
		return 1.f;
	}

	virtual void axKillTrigger()
	{

	}
};

NEPHILIM_NS_END
#endif // NephilimAxTarget_h__
