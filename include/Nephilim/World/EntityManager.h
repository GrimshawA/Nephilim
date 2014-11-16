#ifndef NephilimRazerEntityManager_h__
#define NephilimRazerEntityManager_h__

#include <Nephilim/Platform.h>

#include <vector>

NEPHILIM_NS_BEGIN

/// Define the entity type. All entities are uniquely identified by an unique value only
typedef Int32 TEntity;

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
	std::vector<TEntity> entities;

	TEntity nextAssignment = 1;
};

NEPHILIM_NS_END
#endif // NephilimRazerEntity_h__
