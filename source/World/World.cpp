#include <Nephilim/World/World.h>
#include <Nephilim/World/CTransform.h>
#include <Nephilim/World/CStaticMesh.h>
#include <Nephilim/World/CTransform.h>
#include <Nephilim/World/CSprite.h>
#include <Nephilim/World/CInput.h>
#include <Nephilim/World/CCameraLens.h>
#include <Nephilim/World/CSkeletalMesh.h>
#include <Nephilim/World/CColliderBox.h>

#include <Nephilim/Logger.h>
#include <Nephilim/NxMath.h>

NEPHILIM_NS_BEGIN

World::World()
{
	// Init some component managers
	createDefaultComponentManager<CTransform>();
	createDefaultComponentManager<CStaticMesh>();
	createDefaultComponentManager<CSprite>();
	createDefaultComponentManager<CColliderBox>();
	createDefaultComponentManager<CCameraLens>();
	createDefaultComponentManager<CInput>();
//	createDefaultComponentManager<ComponentSkinnedModel>();

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

/// This is the most basic prefab instancing class
/// Returns a pointer to the allocated object if applicable
GameObject* World::spawnPrefab(const Prefab& prefab)
{
	GameObject* GeneratedObject = nullptr;

	String ClassName = prefab.getRootClassName();

	// We're spawning an actor directly
	if (ClassName == "Actor")
	{
		Actor* actor = spawnActor();

		for (auto it = prefab.objectData.cbegin(); it != prefab.objectData.cend(); ++it)
		{
			if (it->tag == "Sprite")
			{
				SpriteComponent* spriteComponent = actor->createComponent<SpriteComponent>();
				spriteComponent->s.setSize(it->get("width").toFloat(), it->get("height").toFloat());
				spriteComponent->s.tex = it->get("asset");
			}
		}

		GeneratedObject = actor;	

		Log("Actor spawned from a prefab");
	}

	return GeneratedObject;
}

/// Get one of the currently loaded levels
Level* World::getLevel(std::size_t index)
{
	return levels[index];
}

/// Spawns an actor
Actor* World::spawnActor()
{
	Actor* actor = new Actor();
	actor->mWorld = this;
	actors.push_back(actor);
	return actor;
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
	system->mWorld = this;
	mRegisteredSystems.push_back(system);
}

/// Create and return a new entity
Entity World::createEntity()
{
	// Create new entity
	Entity entity;
	entity.id = 0;
	entity.id = entityManager.nextAssignment.id++;
	entityManager.entities.push_back(entity);
	return entity;
}

/// Removes the entity if it is in the scene
void World::removeEntity(Entity entity)
{
	entityManager.destroy(entity);

	for (auto it = componentManagers.begin(); it != componentManagers.end(); ++it)
	{
		it->second->removeComponentsFromEntity(entity);
	}
}

Entity World::getEntityByIndex(std::size_t index)
{
	return entityManager.entities[index];
}

void World::destroyActor(Actor* actor)
{
	delete actor;
}

NEPHILIM_NS_END