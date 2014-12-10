#ifndef NephilimRazerEntityManager_h__
#define NephilimRazerEntityManager_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Entity.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class EntityManager
	\brief Manages N entities at any given time

	This class is exclusively to manage alive entities,
	each manager controls N unique entities.

	Usually, only one EntityManager will be used for the entire game,
	but this is flexible for more interesting usages.
*/
class NEPHILIM_API EntityManager
{
public:
	std::vector<Entity> entities;

	Entity nextAssignment;

public:

	EntityManager()
	{
		nextAssignment.id = 1;
	}

	/// Destroy this entity
	void destroy(Entity entity);
};

NEPHILIM_NS_END
#endif // NephilimRazerEntity_h__
