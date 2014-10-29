#include <Nephilim/Razer/World.h>
#include <Nephilim/Razer/CTransform.h>

NEPHILIM_NS_BEGIN

World::World()
//: nextAssignID(1)
{
}

/// Cumulate the transform hierarchy so all model matrices are computed and can be used for rendering
void World::updateTransformHierarchy()
{

	//ComponentArray<CTransform>& transforms = getComponentList<CTransform>();
}

/// Registers a system to this scene
void World::registerSystem(System* system)
{
	system->mScene = this;
	mRegisteredSystems.push_back(system);
}

/// Create and return a new entity
TEntity World::createEntity()
{
	// Create new entity
	TEntity entity = 0;
	entity = entityManager.nextAssignment++;
	entityManager.entities.push_back(entity);
	return entity;
}

/// Removes the entity if it is in the scene
void World::removeEntity(Int32 id)
{
/*	for(size_t i = 0; i < mEntities.size(); ++i)
	{
		if(mEntities[i] == id)
		{
			mEntities.erase(mEntities.begin() + i);
			return;
		}
	}*/
}

TEntity World::getEntityByIndex(std::size_t index)
{
	return entityManager.entities[index];
}

NEPHILIM_NS_END