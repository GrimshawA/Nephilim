#include <Nephilim/AxColor.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

AxAlpha::AxAlpha()
: AxBase()
, m_easing(AxEasingFunction::QuarticInterpolation)
{

}

AxAlpha::AxAlpha(Uint8 alpha, float duration)
: AxBase(duration)
, m_easing(AxEasingFunction::QuarticInterpolation)
, m_end(alpha / 255)
{

}

void AxAlpha::deduceInitialParameters()
{
	if(getTargetCount() > 0)
	{
		m_begin = m_targets.front()->axGetAlpha();
	}
}

float AxAlpha::update(float delta)
{
	m_elapsed += delta;

	float result = m_easing(m_elapsed, m_begin, m_end - m_begin, m_duration );

	if(m_elapsed > m_duration) result = m_end;

	//Log("Alpha updating %d", result);

	for(TargetIterator it = m_targets.begin(); it != m_targets.end(); ++it)
	{
		(*it)->axSetAlpha(result);
	}

	return 0.f;
}
NEPHILIM_NS_END