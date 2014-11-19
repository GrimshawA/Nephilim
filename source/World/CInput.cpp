#include <Nephilim/World/CInput.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

typedef void(*FunctionFunc)(float);

/// Emit signals for the given axis
void CInput::fireAxis(const String& axisName)
{
	axisMappings[axisName].binding.emit(1.f);
}

void CInput::fireAction(const String& actionName)
{
	actionBindings[actionName].binding();
}

NEPHILIM_NS_END

