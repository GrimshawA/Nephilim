#ifndef NephilimRazerComponentManager_h__
#define NephilimRazerComponentManager_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/Component.h>
#include <Nephilim/Razer/EntityManager.h>

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN
namespace rzr {

/**
	\class ComponentManager
	\brief Base class for component storage and utility

	This is the base class for component storage.
	Once this interface is implemented, it becomes a fully
	fledged warehouse of a given component type, along with
	utility to access the components and alter them.

	The common interface standard makes sure all component managers
	will work well with a few functions, namely the component handles.

	The component handler is a integer based reference system. Depending
	on the component manager implementation, a pointer reference can quickly
	become a dangling pointer, and there is no way to detect that in user code unless
	callbacks are implemented, adding extra hassle.

	Because of that, an integer based component system is used, which will usually
	provide a cache efficient O(1) access to the component, with really quick validity checks
	that can't fail.

	This handle system is great for fast lookups, detecting components that were already discarded,
	and it allows the array to stay tightly packed with no wasted memory.

	The main restriction of component managers is that they manage one type of component only.

	TEntity is what uniquely identifies an Entity, the engine can be configured for 64 bits TEntity, but usually is a 32 bit integer.
	Since there is this standard, all components or clusters are mapped to entities with this ID. Regardless of what it stands for.

	The user is also free to write custom component managers which hold the components in any way they want, but its good if those managers
	conform to the standard for compatibility with other systems.
*/
class NEPHILIM_API ComponentManager
{
public:
	
	/// Get the number of components being used (not the amount allocated by the pool)
	virtual std::size_t getInstanceCount();

	/// Get a component from the entity
	virtual Component* getComponentFromEntity(TEntity e);

	/// Creates a new component mapped to an entity
	virtual Component* createComponentForEntity(TEntity e);

	/// All managers must ensure that all their allocations are freed upon destruction
	virtual ~ComponentManager();
};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentManager_h__
