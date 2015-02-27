#include <Nephilim/World/World.h>
#include <Nephilim/World/Landscape.h>

#include <Nephilim/World/Systems/PhysicsSystem.h>
#include <Nephilim/World/Systems/AudioSystem.h>
#include <Nephilim/World/Systems/NetworkSystem.h>

#include <Nephilim/World/Components/AStaticMeshComponent.h>
#include <Nephilim/World/Components/ASpriteComponent.h>
#include <Nephilim/World/Components/AInputComponent.h>
#include <Nephilim/World/Components/ACameraComponent.h>
#include <Nephilim/World/Components/ABoxComponent.h>

#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/Math.h>
#include <Nephilim/Foundation/PluginLoader.h>
#include <Nephilim/Foundation/Transform.h>

#include <Nephilim/Game/GameCore.h>
#include <Nephilim/Graphics/Window.h>

NEPHILIM_NS_BEGIN

World::World()
: mEnabled(true)
, mSimulationOnly(false)
{
	Level* defaultLevel = new Level();
	mPersistentLevel = defaultLevel;
	levels.push_back(defaultLevel);

	WorldViewport mainViewport;
	_viewports.push_back(mainViewport);

	createNetworkSystem<NetworkSystem>();

	_renderSystem = createRenderSystem<RenderSystemDefault>();
	_renderSystem->mRenderer = GraphicsDevice::instance();
}

/// Called after having the opportunity to set some initial settings
void World::initialize()
{

}

/// Step the world state forward
void World::update(const Time& deltaTime)
{
	for (std::size_t i = 0; i < mRegisteredSystems.size(); ++i)
	{
		mRegisteredSystems[i]->update(deltaTime);
	}

	for (auto a : mPersistentLevel->actors)
	{
		a->update(deltaTime);
	}
}

/// Get the window-space coordinate of where the point lies in
Vec2<int> World::getScreenCoordinate(Vector3D point)
{
	Vec2<int> screenSpacePoint(0,0);

	if (_camera)
	{
		Vector2D homo = _camera->worldToHomogeneous(point);
		homo.x += 1.f;
		homo.x /= 2.f;

		homo.y += 1.f;
		homo.y /= 2.f;
		homo.y = 1.f - homo.y;

		homo.x *= _game->getWindow()->width();
		homo.y *= _game->getWindow()->width();

		screenSpacePoint.x = static_cast<int>(homo.x);
		screenSpacePoint.y = static_cast<int>(homo.y);
	}

	return screenSpacePoint;
}

/// This will convert a window-space coordinate into a world position
/// Depends on the camera being orthogonal to the Z=0 plane
Vector2D World::getWorldCoordinate2D(Vec2<int> point)
{
	Vector2D worldPoint(0.f, 0.f);

	if (_camera)
	{
		mat4 cam = _camera->getCombinedMatrix();

		Vector2D homo = _game->getWindow()->convertToHomogeneousCoordinate(point);
		Vector4D worldCoordinate = cam.inverse() * Vector4D(homo.x, homo.y, 0.f, 1.f);

		worldPoint.x = worldCoordinate.x;
		worldPoint.y = worldCoordinate.y;
	}

	return worldPoint;
}


/// Set the player controller for this world if applicable (clients only)
/// The World _owns_ the object and destroys it when releasing
void World::setPlayerController(PlayerController* playerController)
{
	_playerController.reset(playerController);
	_playerController->_world = this;
}

/// Load a level into memory by its name
/// This requires that the level is previously indexed into this world
bool World::loadLevel(const String& name, bool async)
{
	mPersistentLevel = new Level();
	mPersistentLevel->name = name;
	return false;
}

/// Load directly the new level into this world, and index it too
bool World::loadLevel(Level* level)
{
	return false;
}


/// Unload every level currently active
/// If this world isn't multi level, it will only destroy the current level, if applicable
/// The main use of the function is to revert the world to an empty state before loading the next level
void World::unloadLevels()
{
	// TODO; support multi level
	if (mPersistentLevel)
	{
		delete mPersistentLevel;
		mPersistentLevel = nullptr;
	}
}


/// Create a PhysicsSystem from its name
/// This means the physics system will be instanced via factory (plugin or not)
PhysicsSystem* World::createPhysicsSystem(const String& name)
{
	PhysicsSystem* physicsSystem = nullptr;

	// Prepare the angel script behavior, the dirty way
	typedef PhysicsSystem* (*InstanceLoader_Fn2)();

	// FIX THE LEAK, PLUGINS ARE GAME WIDE
	PluginLoader* physicsPlugin = new PluginLoader(name);
	if (physicsPlugin->isLoaded())
	{
		InstanceLoader_Fn2 f = (InstanceLoader_Fn2)physicsPlugin->getFunctionAddress("createPhysicsSystem");
		if (f)
		{
			physicsSystem = f();
			attachSystem(physicsSystem);
			Log("GOT PHYSICS!");
		}
	}

	return physicsSystem;
}

/// Create a audio system from a plugin or factory
AudioSystem* World::createAudioSystem(const String& name)
{
	AudioSystem* audioSystem = nullptr;

	// Prepare the angel script behavior, the dirty way
	typedef AudioSystem* (*InstanceLoader_Fn2)();

	// FIX THE LEAK, PLUGINS ARE GAME WIDE
	PluginLoader* audioPlugin = new PluginLoader(name);
	if (audioPlugin->isLoaded())
	{
		InstanceLoader_Fn2 f = (InstanceLoader_Fn2)audioPlugin->getFunctionAddress("createAudioSystem");
		if (f)
		{
			audioSystem = f();
			attachSystem(audioSystem);
			Log("GOT AUDIO!");
		}
	}

	return audioSystem;
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
	actor->_world = this;
	mPersistentLevel->actors.push_back(actor);
	return actor;
}

/// Returns the first actor it finds with that name or nullptr
Actor* World::getActorByName(const String& _name)
{
	for (auto actor : mPersistentLevel->actors)
	{
		if (actor->mName == _name)
		{
			//Log("Compare %s with %s", actor->mName.c_str(), _na)
			return actor;
		}
	}
	return nullptr;
}

/// Returns the Actor with the given ID
Actor* World::getActorByUUID(uint32_t _uuid)
{
	for (auto actor : mPersistentLevel->actors)
	{
		if (actor->uuid == _uuid)
		{
			//Log("Compare %s with %s", actor->mName.c_str(), _na)
			return actor;
		}
	}
	return nullptr;
}

/// Get the total numbers of spawned actors
int World::getActorCount()
{
	return mPersistentLevel->actors.size();
}

/// Spawn a vanilla Landscape (not subclassed)
Landscape* World::spawnLandscape()
{
	// Landscapes need to belong to their own levels, they are heavier map objects and need to be culled more efficiently
	if (mPersistentLevel)
	{
		Landscape* land = new Landscape();
		mPersistentLevel->landscapes.push_back(land);
		return land;
	}

	return nullptr;
}

/// Registers a system to this scene
void World::attachSystem(System* system)
{
	system->_World = this;
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