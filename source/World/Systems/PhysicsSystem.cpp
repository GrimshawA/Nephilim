#include <Nephilim/World/Systems/PhysicsSystem.h>

NEPHILIM_NS_BEGIN

/// Get the name of this PhysicsSystem
/// Used by implementations to name themselves, as they can be fully abstracted in plugins
String PhysicsSystem::getName()
{
	return "Null";
}

NEPHILIM_NS_END