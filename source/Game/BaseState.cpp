#include <Nephilim/Game/BaseState.h>

NEPHILIM_NS_BEGIN

/// Simplest way to call a function in all the attached scripts
/// No error handling or checking
void callScriptFunction(const String& name)
{

}

/// Check how many scripts are attached to this state
std::size_t getNumAttachedScripts()
{
	return 0;
}

NEPHILIM_NS_END