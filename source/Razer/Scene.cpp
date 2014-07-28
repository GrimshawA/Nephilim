#include <Nephilim/Razer/Scene.h>
#include <Nephilim/Razer/Entity.inl>

NEPHILIM_NS_BEGIN
namespace rzr{

Scene::Scene()
: nextAssignID(1)
{
}

/// Registers a system to this scene
void Scene::registerSystem(System* system)
{
	system->mScene = this;
	mRegisteredSystems.push_back(system);
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

/// Removes the entity if it is in the scene
void Scene::removeEntity(Int32 id)
{
	for(size_t i = 0; i < mEntities.size(); ++i)
	{
		if(mEntities[i].mId == id)
		{
			mEntities.erase(mEntities.begin() + i);
			return;
		}
	}
}

Entity Scene::getEntityByIndex(std::size_t index)
{
	Entity entityRef;
	entityRef.id = mEntities[index].mId;
	entityRef.mScene = this;
	return entityRef;
}

Entity Scene::getEntityById(Int32 id)
{
	Entity entityRef;
	entityRef.id = 0;
	for(std::size_t i = 0; i < mEntities.size(); ++i)
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