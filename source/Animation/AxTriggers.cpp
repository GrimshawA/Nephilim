#include <Nephilim/AxTriggers.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

bool AxKillTrigger::isOver()
{
	return true;
}

float AxKillTrigger::update(float delta)
{
	Log("KILL BUTTON");
	for(TargetIterator it = m_targets.begin(); it != m_targets.end(); ++it)
	{
		(*it)->axKillTrigger();
	}
	return 0.f;
}


NEPHILIM_NS_END