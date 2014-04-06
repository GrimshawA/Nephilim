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

Entity Scene::getEntityByIndex(size_t index)
{
	Entity entityRef;
	entityRef.id = mEntities[index].mId;
	entityRef.mScene = this;
	return entityRef;
}

Entity Scene::getEntityById(Int32 id)
{
	Entity entityRef;
	for(size_t i = 0; i < mEntities.size(); ++i)
	{
		if(mEntities[i].mId == id)
		{
			entityRef.id = mEntities[i].mId;
			entityRef.mScene = this;
		}
	}
	return entityRef;
}

};
NEPHILIM_NS_END