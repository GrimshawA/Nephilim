#ifndef NephilimAxColor_h__
#define NephilimAxColor_h__

#include "Platform.h"
#include "AxBase.h"
#include "AxEasing.h"

NEPHILIM_NS_BEGIN

class NEPHILIM_API AxAlpha : public AxBase
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
