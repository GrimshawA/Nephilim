#ifndef NephilimActor_h__
#define NephilimActor_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/CTransform.h>

NEPHILIM_NS_BEGIN

class World;

/**
	\class Actor
	\brief Represents an entity in a game world

	This class is used for managing dynamic entities
	in a game world. Usually, vehicles, characters,
	pickups and other props are composed by Actors.

	This is a higher level abstraction than using the World's 
	low level component-based structures.
*/
class NEPHILIM_API Actor
{
private:
	friend class World; ///< World can access private members as he instances Actors

	/// Pointer to the World instance that created this actor
	World* mWorld = nullptr;

public:
	/// Get the world instance that created this actor
	World* getWorld();

	/// Get the transform of this Actor
	/// This is the transform that converts anything in actor space to world space
	CTransform getTransform();

	/// Destroy this actor
	/// As soon as this function is called, the Actor object may not be used anymore
	void destroy();

};

NEPHILIM_NS_END
#endif // NephilimActor_h__
