#ifndef NephilimScene_h__
#define NephilimScene_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/Entity.h>

#include <vector>

NEPHILIM_NS_BEGIN
namespace rzr {

/**
	\class Scene
	\brief Represents a 3D world
*/
class NEPHILIM_API Scene
{
public:
	Scene();

	/// Create and return a new entity
	Entity createEntity();


	std::vector<EntityInternal> mEntities;
	EntityInternal nextAssignID;
};
};
NEPHILIM_NS_END
#endif // NephilimScene_h__
