#ifndef NephilimScene_h__
#define NephilimScene_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
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

#include <vector>
#include <map>

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

	/// Name of this world
	String name;

	/// With this flag set to true, the world can load many levels at once
	bool multiLevel = true;

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

public:
	World();

	/// Load a level into memory by its name
	/// This requires that the level is previously indexed into this world
	bool loadLevel(const String& name);

	/// Load directly the new level into this world, and index it too
	bool loadLevel(Level* level);

	/// Get one of the currently loaded levels
	Level* getLevel(std::size_t index = 0);

	/// Spawns an actor
	Actor* spawnActor();

	/// This function will produce an object in the world from a prefab definition
	/// Returns a pointer to the allocated object if applicable, its up to the user to determine its actual type and manage that
	/// This function is not recommended use. One should refer to the prefab by name, and the World will look it up by itself.
	/// This is only for convenience, for quickly spawning some objects from a quickly hacked together definition.
	GameObject* spawnPrefab(const Prefab& prefab);

	/// Variant that allows to spawn the entity/actor/etc in a given location and orientation directly
	GameObject* spawnPrefab(const Prefab& prefab, Vector3D location = Vector3D(0.f, 0.f, 0.f), Quaternion orientation = Quaternion::identity);

	/// Spawns an actor with type T (must be a subclass of Actor)
	template<typename T>
	T* spawnActor();

	/// Destroys an actor
	void destroyActor(Actor* actor);


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
