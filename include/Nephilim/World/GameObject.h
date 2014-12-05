#ifndef NephilimGameObject_h__
#define NephilimGameObject_h__

#include <Nephilim/Platform.h>
#include <stdint.h>

NEPHILIM_NS_BEGIN

/**
	\class GameObject
	\brief Base class for all objects that can be spawned in the world

	This is the root class for every instance in the world. However, there may be objects in a level
	that are property-centric, meaning they don't have an instance of a class at all are bound by different rules.

	However, it is planned that all or mostly all relevant things in the world are instanced and subclasses of GameObject.

	GameObject is not polymorphic but it can contain data. This is to reduce overhead to a minimum.

	---------------

	All game objects have a 32 bit integer ID. This allows more than 4 billion unique ID's, which is more than enough to any imaginable game,
	and could be overcomed easily in any case. Thus, 64 bit integer naming isn't required, as ID's will usually be handles too, and indexing into
	a storage buffer that big is also extremely unlikely. Also, in case of networking, things like Actor pointers are meaningless, and using their
	index would quickly turn into hell as things could reorder due to synch problems. So all actors and all objects carry this ID, for networking,
	for inherent compatibility with the property data sets in the pure ECS. GameObjects can also be used as mere stack based entity ID wrappers,
	as they are extremely lightweight. They are also extremely important for concurrent live editing.
*/
class NEPHILIM_API GameObject
{
public:	

	/// Unique ID
	uint32_t uuid;

};

NEPHILIM_NS_END
#endif // NephilimGameObject_h__
