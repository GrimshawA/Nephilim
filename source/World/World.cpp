#include <Nephilim/World/World.h>
#include <Nephilim/World/CTransform.h>

#include <Nephilim/World/CMesh.h>
#include <Nephilim/World/CTransform.h>
#include <Nephilim/World/CSprite.h>
#include <Nephilim/World/CCamera.h>
#include <Nephilim/World/CSkinnedMesh.h>

NEPHILIM_NS_BEGIN

World::World()
{
	// Init some component managers
	createDefaultComponentManager<CTransform>();
	createDefaultComponentManager<CMesh>();
	createDefaultComponentManager<CSprite>();
	createDefaultComponentManager<CCamera>();
	createDefaultComponentManager<ComponentSkinnedModel>();
}

/// Spawns an actor
Actor* World::spawnActor()
{
	return new Actor();
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

void World::destroyActor(Actor* actor)
{
	delete actor;
}

NEPHILIM_NS_END