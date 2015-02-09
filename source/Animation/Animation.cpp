#include <Nephilim/Animation/Animation.h>

#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

Animation::Animation()
: m_looping(false)
, m_duration(0.f)
, m_elapsed(0.f)
{

}

/// Initialize with a duration
Animation::Animation(float duration)
: m_looping(false)
, m_duration(duration)
, m_elapsed(0.f)
{

}

Animation::~Animation()
{
	//Log("AxBase destructor");
}

void Animation::deduceInitialParameters()
{

}

void Animation::addTarget(AxTarget* target)
{
	m_targets.push_back(target);
}

int Animation::getTargetCount()
{
	return m_targets.size();
}

bool Animation::isOver()
{
	return ((m_elapsed > m_duration) && !m_looping);
}

/// Get the duration of the animation
float Animation::getDuration()
{
	return m_duration;
}

NEPHILIM_NS_END
