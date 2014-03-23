#include <Nephilim/Razer/Scene.h>

NEPHILIM_NS_BEGIN
namespace rzr{

Scene::Scene()
: nextAssignID(1)
{
}

/// Create and return a new entity
Entity Scene::createEntity()
{
	// Create new entity
	EntityInternal entity;
	entity.mId = nextAssignID.mId++;	
	mEntities.push_back(entity);

	// Return a reference
	Entity entityRef;
	entityRef.mScene = this;
	entityRef.id = entity.mId;
	return entityRef;
}

};
NEPHILIM_NS_END