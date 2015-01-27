#include <Nephilim/World/AScriptComponent.h>
#include <Nephilim/World/World.h>

#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

void AScriptComponent::tickScript()
{
	if (_script)
	{
		_script->callOnObject("void Tick()", object);
		//_script->call("void print2()");
	}
}

NEPHILIM_NS_END