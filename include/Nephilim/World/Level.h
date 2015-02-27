#ifndef NephilimLevel_h__
#define NephilimLevel_h__

#include <Nephilim/Foundation/Object.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/Foundation/String.h>

#include <Nephilim/World/ComponentWarehouse.h>
#include <Nephilim/World/EntityManager.h>

#include <Nephilim/World/Actor.h>
#include <Nephilim/World/Components/ASpriteComponent.h>
#include <Nephilim/World/Systems/PhysicsSystem.h>

#include <vector>
#include <typeindex>

NEPHILIM_NS_BEGIN

class World;
class Landscape;
class Prefab;

/**
	\class Level
	\brief A finite sized domain with level data

	Levels are essential; They are a complex containers of world data
	with many uses. One World always has 1 or more levels loaded into it,
	otherwise its useless. These are used to spawn objects and their components
	etc.  Levels are independent from each other but they can cross-reference in 
	some ways.

	These should always be used with the World instance owning it, never by themselves.

	There is a maximum size for each level, which defined by a constant. This is needed
	to ensure all things positioned inside this level with floating point coordinates,
	stay with valid numbers.

	All things inside a Level will usually have a coordinate system relative to the Level
	origin. This is a big help for keeping big worlds without precision issues.

	Each level may have one physics system only (can be shared with other levels).
	This allows to put levels inside levels with different physics systems, as well as compartmentalize
	the physics for streaming, among other uses.
*/
class NEPHILIM_API Level : public Object
{
public:
	/// The dimensions of the level, this computes the absolute bounding box
	float width, height, depth;

	/// The unique name of this level
	String name;

	/// World that has this level loaded
	World* world;

	/// The physics system responsible for handling the physics of this Level
	RefObjectPtr<PhysicsSystem> physicsSystem;

	/// Landscape array of this level
	std::vector<Landscape*> landscapes;

	/// List of all spawned actors in this level
	std::vector<Actor*>     actors;

	/// All the game objects instanced in this Level
	std::vector<GameObject*> gameObjects;

public:

	/// Where all the components are stored, nothing is hardcoded
	/// But rather its all a dynamic soup of components, which the systems will have to deal with
	/// This way Level remains incredibly flexible to support any game
	ComponentWarehouse componentWarehouse;

	EntityManager entityManager;

public:

	/// Default construction of a level object
	Level();

	/// Ensure all stuff goes down when the level is destroyed
	~Level();

	/// Get total number of GameObject and its subclasses spawned in this Level
	int32_t getGameObjectCount();

	/// Write this level to a binary file
	bool write(const String& filename);

	/// Read data from a binary file into this Level
	bool read(const String& filename);

	/// Utility to quickly spawn a point light into our world
	void createPointLight(Vector3D position, Vector3D lightColor);

	/// Instance a new game object from a prefab
	GameObject* instance(const Prefab& prefab);
};

NEPHILIM_NS_END
#endif // NephilimLevel_h__
