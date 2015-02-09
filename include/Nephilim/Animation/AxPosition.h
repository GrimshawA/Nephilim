#ifndef NephilimAxPosition_h__
#define NephilimAxPosition_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Animation/Animation.h>

#include "AxEasing.h"
#include <Nephilim/Foundation/Vector.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API AxPosition2D : public Animation
{
public:
	AxPosition2D();

	AxPosition2D(float target_x, float target_y, float duration);

	~AxPosition2D();

	/// Attempts to deduce initial animation parameters by looking at the targets
	virtual void deduceInitialParameters();

	float update(float delta);

private:
	vec2 m_begin;
	vec2 m_end;
	AxEasingFunction m_easing;
};

NEPHILIM_NS_END
#endif // NephilimAxPosition_h__