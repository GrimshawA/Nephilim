#ifndef NephilimPhysicsSystem_h__
#define NephilimPhysicsSystem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/World/Systems/System.h>

NEPHILIM_NS_BEGIN


/**
	\class PhysicsSystem
	\brief Interface for plugging different physics engines into the scene
*/
class NEPHILIM_API PhysicsSystem : public System
{
public:

	/// Get the name of this PhysicsSystem
	/// Used by implementations to name themselves, as they can be fully abstracted in plugins
	virtual String getName();
};

NEPHILIM_NS_END
#endif // NephilimPhysicsSystem_h__