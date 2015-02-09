#ifndef NephilimAxColor_h__
#define NephilimAxColor_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Animation/Animation.h>

#include "AxEasing.h"

NEPHILIM_NS_BEGIN

class NEPHILIM_API AxAlpha : public Animation
{
public:

	AxAlpha();

	AxAlpha(Uint8 alpha, float duration);

	void deduceInitialParameters();

	float update(float delta);

	float m_begin;
	float m_end;
	AxEasingFunction m_easing;
};

NEPHILIM_NS_END
#endif // NephilimAxColor_h__
