#include <Nephilim/AxBase.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

AxBase::AxBase()
: m_looping(false)
, m_duration(0.f)
, m_elapsed(0.f)
{

}

/// Initialize with a duration
AxBase::AxBase(float duration)
: m_looping(false)
, m_duration(duration)
, m_elapsed(0.f)
{

}

AxBase::~AxBase()
{
	//Log("AxBase destructor");
}

void AxBase::deduceInitialParameters()
{

}

void AxBase::addTarget(AxTarget* target)
{
	m_targets.push_back(target);
}

int AxBase::getTargetCount()
{
	return m_targets.size();
}

bool AxBase::isOver()
{
	return ((m_elapsed > m_duration) && !m_looping);
}

/// Get the duration of the animation
float AxBase::getDuration()
{
	return m_duration;
}

NEPHILIM_NS_END
