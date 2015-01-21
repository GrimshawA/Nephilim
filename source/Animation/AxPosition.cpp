#include <Nephilim/AxPosition.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

AxPosition2D::AxPosition2D()
: AxBase()
{

}

AxPosition2D::AxPosition2D(float target_x, float target_y, float duration)
: AxBase()
, m_end(target_x, target_y)
, m_easing(AxEasingFunction::QuarticInterpolation)
{
	//Log("Position created");
	m_duration = duration;
}

AxPosition2D::~AxPosition2D()
{
	//Log("Position destroyed");
}

void AxPosition2D::deduceInitialParameters()
{
	if(getTargetCount() > 0)
	{
		m_begin = m_targets.front()->axGetPosition2D();
	}
}

float AxPosition2D::update(float delta)
{
	//Log("Position set %f to %f", m_begin.x, m_end.y);
	m_elapsed += delta;

	vec2 result;
	result.x = m_easing(m_elapsed, m_begin.x, m_end.x - m_begin.x, m_duration );
	result.y = m_easing(m_elapsed, m_begin.y, m_end.y - m_begin.y, m_duration );

	for(TargetIterator it = m_targets.begin(); it != m_targets.end(); ++it)
	{
		(*it)->axSetPosition2D(result);
	}

	return 0.f;
}


NEPHILIM_NS_END