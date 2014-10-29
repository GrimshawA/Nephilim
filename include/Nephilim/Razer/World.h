#ifndef NephilimScene_h__
#define NephilimScene_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Razer/EntityManager.h>
#include <Nephilim/Razer/ComponentManager.h>
#include <Nephilim/Razer/System.h>
#include <Nephilim/Razer/Component.h>

#include <Nephilim/Razer/ComponentArray.h>

#include <vector>
#include <map>



NEPHILIM_NS_BEGIN
using namespace rzr;
/**
	\class World
	\brief Contains a single world space, filled with entities and components
*/
class NEPHILIM_API World
{
public:

	///< Name of this world
	String name;

	/// This class is responsible for managing the entities alive
	EntityManager entityManager;

	/// Component storage units
	/// &type_id(component_type) -> ComponentList
	std::map<std::type_index, ComponentManager*> componentManagers;

	/// The registered systems with this scene
	/// Each of these systems, once hooked can observe the scene and get callbacks from it automatically
	std::vector<System*> mRegisteredSystems;


public:
	World();

	/// Allocate a component manager to type T as a ComponentArray<T>
	template<typename T>
	void createDefaultComponentManager();

	/// Cumulate the transform hierarchy so all model matrices are computed and can be used for rendering
	void updateTransformHierarchy();

	/// Registers a system to this scene
	void registerSystem(System* system);

	/// Get the current component manager handling the type T
	template<typename T>
	ComponentManager* getComponentManager();

	/// Create and return a new entity
	TEntity createEntity();

	/// Removes the entity if it is in the scene
	void removeEntity(Int32 id);

	TEntity getEntityByIndex(std::size_t index);

	template<typename T>
	void createComponent(T c, TEntity e);
};

template<typename T>
ComponentManager* World::getComponentManager()
{
	if (componentManagers.find(std::type_index(typeid(T))) == componentManagers.end())
	{
		componentManagers[std::type_index(typeid(T))] = new ComponentArray<T>();
	}

	return componentManagers[std::type_index(typeid(T))];
}

// -- Copy a component to its manager and bind to entity e
template<typename T>
void World::createComponent(T c, TEntity e)
{
	ComponentManager* componentManager = getComponentManager<T>();

	T* component = static_cast<T*>(componentManager->createComponentForEntity(e));
	*component = c;
}

template<typename T>
void World::createDefaultComponentManager()
{
	if (componentManagers.find(std::type_index(typeid(T))) != componentManagers.end())
	{
		delete componentManagers[std::type_index(typeid(T))];
		componentManagers.erase(componentManagers.find(std::type_index(typeid(T))));
	}
	
	componentManagers[std::type_index(typeid(T))] = new ComponentArray<T>();
}

NEPHILIM_NS_END
#endif // NephilimScene_h__
