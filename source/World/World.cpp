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

	Level* defaultLevel = new Level();
	levels.push_back(defaultLevel);
}

/// Load a level into memory by its name
/// This requires that the level is previously indexed into this world
bool World::loadLevel(const String& name)
{
	return false;
}

/// Load directly the new level into this world, and index it too
bool World::loadLevel(Level* level)
{
	return false;
}

/// Get one of the currently loaded levels
Level* World::getLevel(std::size_t index)
{
	return levels[index];
}

/// Spawns an actor
Actor* World::spawnActor()
{
	return new Actor();
}

/// Cumulate the transform hierarchy so all model matrices are computed and can be used for rendering
void World::updateTransformHierarchy()
{
	for (std::size_t i = 0; i < actors.size(); ++i)
	{
		if (actors[i]->root != nullptr)
		{

		}
	}
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
	entityManager.destroy(id);

	for (auto it = componentManagers.begin(); it != componentManagers.end(); ++it)
	{
		it->second->removeComponentsFromEntity(id);
	}
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