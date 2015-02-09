#ifndef NephilimWorld_h__
#define NephilimWorld_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Object.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Time.h>

#include <Nephilim/World/GameObject.h>
#include <Nephilim/World/Actor.h>
#include <Nephilim/World/Entity.h>
#include <Nephilim/World/Prefab.h>
#include <Nephilim/World/EntityManager.h>
#include <Nephilim/World/ComponentManager.h>
#include <Nephilim/World/Systems/System.h>
#include <Nephilim/World/Component.h>
#include <Nephilim/World/ComponentArray.h>
#include <Nephilim/World/Level.h>
#include <Nephilim/World/WorldViewport.h>
#include <Nephilim/World/PlayerController.h>
#include <nephilim/World/Systems/RenderSystemDefault.h>

#include <vector>
#include <map>
#include <memory>

NEPHILIM_NS_BEGIN

class GraphicsDevice;
class GameContent;
class GameCore;
class PhysicsSystem;
class AudioSystem;
class NetworkSystem;
class ACameraComponent;


/**
	\class World
	\brief Game world container

	This class is like a shell for game worlds. You can plug lots of data to it,
	to form single or multi level environments, populated by Component, either
	native or created by the user.

	To make something with this data, one plugs Systems into the World,
	which will make it do interesting things from networking to playing audio,
	rendering itself and so on.

	World objects are rigged to be absolutely powerful from the moment they are
	instanced, yet fully customizable to fit any game's needs.

	Each world indexes a list of Level instances, usually only one, for smaller maps.
	Its mandatory that a Level is indexed before doing anything with it.
*/
class NEPHILIM_API World : public Object
{
public:

	/// Game that owns this world
	GameCore* _game = nullptr;

	/// Whether the World is running or not
	bool mEnabled;

	/// Whether this world is only a simulation not meant to be run with graphics
	bool mSimulationOnly;

	/// The player controller bound to this world at the moment
	std::unique_ptr<PlayerController> _playerController = nullptr;

	/// Currently assigned viewports, usually there is only one except for split screen cases
	std::vector<WorldViewport> _viewports;

	/// Currently bound RenderSystem, used to push frames
	RenderSystem* _renderSystem = nullptr;

	/// Currently bound NetworkSystem, used to synchronize worlds and provide online gameplay
	std::vector<NetworkSystem*> _networkSystems;

	/// Name of this world
	String name;

	/// With this flag set to true, the world can load many levels at once
	bool multiLevel = false;

	/// This class is responsible for managing the entities alive
	EntityManager entityManager;


	/// The registered systems with this scene
	/// Each of these systems, once hooked can observe the scene and get callbacks from it automatically
	std::vector<System*> mRegisteredSystems;

	/// The graphics device used to render this world
	GraphicsDevice* graphicsDevice = nullptr;

	/// The content manager that provides assets for this world
	GameContent* contentManager = nullptr;

	/// Array of levels in this world
	std::vector<Level*> levels;

	/// On construction, the persistent level is instanced and ready to go
	/// Unless we are on the multi-level streaming mode, there is only one active level ever
	Level* mPersistentLevel;

	/// Current camera that renders this world
	ACameraComponent* _camera = nullptr;

public:
	/// Just prepare the world
	World();

	/// Called after having the opportunity to set some initial settings
	void initialize();

	/// Step the world state forward
	void update(const Time& deltaTime);

	/// Set the player controller for this world if applicable (clients only)
	/// The World _owns_ the object and destroys it when releasing
	void setPlayerController(PlayerController* playerController);

	/// Get the window-space coordinate of where the point lies in
	Vec2<int> getScreenCoordinate(Vector3D point);

	/// This will convert a window-space coordinate into a world position
	/// Depends on the camera being orthogonal to the Z=0 plane
	Vector2D getWorldCoordinate2D(Vec2<int> point);
	

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
	GameObject* spawnPrefab(const Prefab& prefab, Vector3D location = Vector3D(0.f, 0.f, 0.f), Quat orientation = Quat::identity);

	/// Spawn a prefab definition directly into the world
	GameObject* spawnPrefab(const String& prefabAsset, Vector3D location = Vector3D(0.f, 0.f, 0.f), Quat orientation = Quat::identity);

	/// Spawns an actor with type T (must be a subclass of Actor)
	template<typename T>
	T* spawnActor();

	/// Spawns an actor with type T (must be a subclass of Actor)
	template<typename T>
	T* spawnActor(Vector3D location, Quat orientation = Quat::identity);

	/// Spawns a vanilla Actor (not subclassed)
	Actor* spawnActor();

	/// Returns the first actor it finds with that name or nullptr
	Actor* getActorByName(const String& _name);

	/// Returns the Actor with the given ID
	Actor* getActorByUUID(uint32_t _uuid);

	/// Destroys an actor
	void destroyActor(Actor* actor);

	/// Get the total numbers of spawned actors
	int getActorCount();

	/// Registers a system to this scene
	void attachSystem(System* system);

	/// Instances a new RenderSystem with type T and initializes it
	/// T must be a derived type of RenderSystem
	template<typename T>
	T* createRenderSystem();

	/// Instances a new NetworkSystem or derived type and registers it
	/// Can optionally remove all previously registered NetworkSystem
	template<typename T>
	T* createNetworkSystem();

	/// Create a PhysicsSystem from its name
	/// This means the physics system will be instanced via factory (plugin or not)
	/// Returns nullptr if it fails
	PhysicsSystem* createPhysicsSystem(const String& name);

	/// Create a audio system from a plugin or factory
	AudioSystem* createAudioSystem(const String& name);

	/// Create and return a new entity
	Entity createEntity();

	/// Removes the entity if it is in the scene
	void removeEntity(Entity entity);

	Entity getEntityByIndex(std::size_t index);

};

/// The template definitions are stored elsewhere
#include <Nephilim/World/World.inl>

NEPHILIM_NS_END
#endif // NephilimWorld_h__
