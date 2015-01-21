#ifndef NephilimScene_h__
#define NephilimScene_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Foundation/Time.h>
#include <Nephilim/World/GameObject.h>
#include <Nephilim/World/Actor.h>
#include <Nephilim/World/Entity.h>
#include <Nephilim/World/Prefab.h>
#include <Nephilim/World/EntityManager.h>
#include <Nephilim/World/ComponentManager.h>
#include <Nephilim/World/System.h>
#include <Nephilim/World/Component.h>
#include <Nephilim/World/ComponentArray.h>
#include <Nephilim/World/Level.h>
#include <Nephilim/World/WorldViewport.h>
#include <Nephilim/World/PlayerController.h>
#include <nephilim/World/RenderSystemDefault.h>

#include <vector>
#include <map>
#include <memory>

NEPHILIM_NS_BEGIN

class GraphicsDevice;
class ContentManager;
class PhysicsSystem;
class AudioSystem;

/**
	\class World
	\brief Contains a single world space, filled with entities and components
*/
class NEPHILIM_API World
{
public:

	/// The player controller bound to this world at the moment
	std::unique_ptr<PlayerController> _playerController = nullptr;

	/// Currently assigned viewports, usually there is only one except for split screen cases
	std::vector<WorldViewport> _viewports;

	/// Name of this world
	String name;

	/// With this flag set to true, the world can load many levels at once
	bool multiLevel = false;

	/// This class is responsible for managing the entities alive
	EntityManager entityManager;

	/// Component storage units
	/// &type_id(component_type) -> ComponentList
	std::map<std::type_index, ComponentManager*> componentManagers;

	/// The registered systems with this scene
	/// Each of these systems, once hooked can observe the scene and get callbacks from it automatically
	std::vector<System*> mRegisteredSystems;

	/// The graphics device used to render this world
	GraphicsDevice* graphicsDevice = nullptr;

	/// The content manager that provides assets for this world
	ContentManager* contentManager = nullptr;

	/// The currently instanced list of actors
	std::vector<Actor*> actors;

	/// Array of levels in this world
	std::vector<Level*> levels;

	/// Current level we have loaded
	/// Unless we are on the multi-level streaming mode, there is only one active level ever
	Level* _currentLevel;

public:
	/// Just prepare the world
	World();

	/// Set the player controller for this world if applicable (clients only)
	/// The World _owns_ the object and destroys it when releasing
	void setPlayerController(PlayerController* playerController);

	/// Load a level into memory by its name
	/// This requires that the level is previously indexed into this world
	/// In async mode, the level will load in parallel and notify when its finished
	/// Otherwise the call will block until the new level is fully ready
	bool loadLevel(const String& name, bool async);

	/// Load directly the new level into this world, and index it too
	bool loadLevel(Level* level);

	/// Unload every level currently active
	/// If this world isn't multi level, it will only destroy the current level, if applicable
	/// The main use of the function is to revert the world to an empty state before loading the next level
	void unloadLevels();

	/// Get one of the currently loaded levels
	Level* getLevel(std::size_t index = 0);

	/// Spawn a vanilla Landscape (not subclassed)
	Landscape* spawnLandscape();

	/// This function will produce an object in the world from a prefab definition
	/// Returns a pointer to the allocated object if applicable, its up to the user to determine its actual type and manage that
	/// This function is not recommended use. One should refer to the prefab by name, and the World will look it up by itself.
	/// This is only for convenience, for quickly spawning some objects from a quickly hacked together definition.
	GameObject* spawnPrefab(const Prefab& prefab);

	/// Variant that allows to spawn the entity/actor/etc in a given location and orientation directly
	GameObject* spawnPrefab(const Prefab& prefab, Vector3D location = Vector3D(0.f, 0.f, 0.f), Quaternion orientation = Quaternion::identity);

	/// Spawn a prefab definition directly into the world
	GameObject* spawnPrefab(const String& prefabAsset, Vector3D location = Vector3D(0.f, 0.f, 0.f), Quaternion orientation = Quaternion::identity);

	/// Spawns an actor with type T (must be a subclass of Actor)
	template<typename T>
	T* spawnActor();

	/// Spawns an actor with type T (must be a subclass of Actor)
	template<typename T>
	T* spawnActor(Vector3D location, Quaternion orientation = Quaternion::identity);

	/// Spawns a vanilla Actor (not subclassed)
	Actor* spawnActor();

	/// Returns the first actor it finds with that name or nullptr
	Actor* getActorByName(const String& _name);

	/// Destroys an actor
	void destroyActor(Actor* actor);

	/// Get the total numbers of spawned actors
	int getActorCount();

	/// Allocate a component manager to type T as a ComponentArray<T>
	template<typename T>
	void createDefaultComponentManager();

	/// Cumulate the transform hierarchy so all model matrices are computed and can be used for rendering
	void updateTransformHierarchy();

	/// Registers a system to this scene
	void registerSystem(System* system);

	/// Instances a new RenderSystem with type T and initializes it
	/// T must be a derived type of RenderSystem
	template<typename T>
	T* createRenderSystem();

	/// Create a PhysicsSystem from its name
	/// This means the physics system will be instanced via factory (plugin or not)
	/// Returns nullptr if it fails
	PhysicsSystem* createPhysicsSystem(const String& name);

	/// Create a audio system from a plugin or factory
	AudioSystem* createAudioSystem(const String& name);

	/// Get the current component manager handling the type T
	template<typename T>
	ComponentManager* getComponentManager();

	/// Create and return a new entity
	Entity createEntity();

	/// Removes the entity if it is in the scene
	void removeEntity(Entity entity);

	Entity getEntityByIndex(std::size_t index);

	template<typename T>
	void createComponent(T c, Entity e);


};

/// The template definitions are stored elsewhere
#include <Nephilim/World/World.inl>

NEPHILIM_NS_END
#endif // NephilimScene_h__
