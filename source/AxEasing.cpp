#include <Nephilim/AxEasing.h>

namespace 
{
	float computelerp(float t,float b,float c,float d){
		return c*t/d + b;
	};

	float computequarticeased(float t,float b,float c,float d){
		t /= d/2;
		if (t < 1) return c/2*t*t*t*t + b;
		t -= 2;
		return -c/2 * (t*t*t*t - 2) + b;
	}
};

NEPHILIM_NS_BEGIN

AxEasingFunction::AxEasingFunction()
{
	m_easeFunction = computelerp;
	m_type = LinearInterpolation;
}

float AxEasingFunction::operator()(float elapsedTime, float startValue, float valueInterval, float duration)
{
	return m_easeFunction(elapsedTime, startValue, valueInterval, duration);
}

void AxEasingFunction::setFunction(NativeEasingFunction function)
{
	switch(function)
	{
	case LinearInterpolation:
		{
			m_easeFunction = computelerp;
			break;
		}
	case QuarticInterpolation:
		{
			m_easeFunction = computequarticeased;
			break;
		}
	}

	m_type = function;
}

void AxEasingFunction::setFunction(easeFuncPtr& funcPtr)
{
	m_easeFunction = funcPtr;
	m_type = Other;
}

NEPHILIM_NS_END