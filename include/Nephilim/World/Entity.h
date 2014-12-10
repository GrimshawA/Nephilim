#ifndef NephilimWorldEntity_h__
#define NephilimWorldEntity_h__

#include <Nephilim/Platform.h>
#include <stdint.h>

NEPHILIM_NS_BEGIN

/**
	\class Entity
	\brief A raw entity ID from the ECS

	An entity is _not_ an object. It is just an integer ID
	to glue components together within the component managers.

	As such, Entity is not meant to be stored in random code
	as if it was an object. It has no methods and is just a POD.

	It is only a class by personal preference. It has no difference from
	a raw integer instead. It just feels safer to use it instead of a typedef only.
*/
class Entity
{
public:
	uint32_t id;
};

// Utilities
bool operator==(Entity& e1, Entity& e2);

bool operator<(const Entity e1, const Entity e2);

NEPHILIM_NS_END
#endif // NephilimWorldEntity_h__
