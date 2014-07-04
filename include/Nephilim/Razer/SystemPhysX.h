#ifndef NephilimSystemPhysX_h__
#define NephilimSystemPhysX_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/System.h>

namespace physx
{
	class PxPhysics;
	class PxScene;
}

NEPHILIM_NS_BEGIN


namespace rzr
{

/**
	\class SystemPhysX
	\brief This system coordinates a single physX simulation, using the data from a Scene
*/
class NEPHILIM_API SystemPhysX : public System
{
public:
	SystemPhysX();

	virtual void update(const Time& deltaTime);

	physx::PxPhysics* mPhysics;
	physx::PxScene* mScene;
};

}
NEPHILIM_NS_END
#endif // NephilimSystemPhysX_h__
