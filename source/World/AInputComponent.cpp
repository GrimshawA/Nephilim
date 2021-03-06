#include <Nephilim/World/AInputComponent.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

typedef void(*FunctionFunc)(float);

/// Emit signals for the given axis
void AInputComponent::fireAxis(const String& axisName)
{
	axisMappings[axisName].binding.emit(1.f);
}

void AInputComponent::fireAction(const String& actionName)
{
	actionBindings[actionName].binding();
}

NEPHILIM_NS_END

