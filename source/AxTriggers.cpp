#include <Nephilim/AxTriggers.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

float AxKillTrigger::update(float delta)
{
	Log("KILL BUTTON");
	return 0.f;
}


NEPHILIM_NS_END