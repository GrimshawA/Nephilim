#include <Nephilim/World/Systems/System.h>

NEPHILIM_NS_BEGIN

System::~System()
{
}

/// Generic update that systems can run
void System::update(const Time& deltaTime)
{
}

/// Get the world this system is attached to
/// Any plugged system has exactly one World attached to it
World* System::getWorld()
{
	return _World;
}

NEPHILIM_NS_END