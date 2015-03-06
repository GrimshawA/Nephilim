#ifndef NephilimGameObject_h__
#define NephilimGameObject_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Object.h>
#include <Nephilim/Foundation/Factory.h>

#include <stdint.h>
#include <vector>

NEPHILIM_NS_BEGIN

class Component;
class World;

/**
	\class GameObject
	\brief Base class for all objects that can be spawned in the world

	This is a component-based entity just like a raw Entity, except it
	is more predictable in a OOP sense. This class is used to pass around
	an actual object representing the game entity with utility functions etc.

	The user and the engine inherits GameObject to provide even more specialized
	subclasses. Actor, Landscape and Blueprint are such examples.

	Any user looking for a pure ECS usage can get by with raw Entity, which is
	GameObject's counterpart. Both interact with components just the same, though,
	and are compatible with the ECS paradigm of implementing the logic in systems,
	except GameObjects can directly define gameplay logic for commodity.

	Every GameObject has a unique identifier, that makes it unique across all levels in the world.
	This ID is crucial for networking simulations, as its how the client and server know they are
	talking about the same thing.
*/
class NEPHILIM_API GameObject : public Object
{
public:	

	/// World this GameObject was instanced in
	World* _world = nullptr;

	/// RTTI
	FClass* _Class = nullptr;

	/// Unique ID
	uint32_t uuid;

	/// The array of components on this Actor
	std::vector<Component*> components;

public:

	/// Get the class RTTI for this game objectc class
	FClass* getClass();

};

NEPHILIM_NS_END
#endif // NephilimGameObject_h__
