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
namespace rzr {

/**
	\class Scene
	\brief Represents a 3D world

	Scene is a container for entities, which by contain components themselves.
	For short, what a scene does is to hold world data, which is simulated by specialized systems.

	In each rendering frame, there is also a specialized system which is able to produce a final image of the world's data
*/
class NEPHILIM_API Scene
{
public:

	/// This class is responsible for managing the entities alive
	EntityManager entityManager;

	/// Component storage units
	/// &type_id(component_type) -> ComponentList
	std::map<std::type_index, ComponentManager*> componentManagers;

	/// The registered systems with this scene
	/// Each of these systems, once hooked can observe the scene and get callbacks from it automatically
	std::vector<System*> mRegisteredSystems;


public:
	Scene();

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
};

template<typename T>
ComponentManager* Scene::getComponentManager()
{
	if (componentManagers.find(std::type_index(typeid(T))) == componentManagers.end())
	{
		componentManagers[std::type_index(typeid(T))] = new ComponentArray<T>();
	}

	return componentManagers[std::type_index(typeid(T))];
}

template<typename T>
void Scene::createDefaultComponentManager()
{
	if (componentManagers.find(std::type_index(typeid(T))) != componentManagers.end())
	{
		delete componentManagers[std::type_index(typeid(T))];
		componentManagers.erase(componentManagers.find(std::type_index(typeid(T))));
	}
	
	componentManagers[std::type_index(typeid(T))] = new ComponentArray<T>();
}

/*
template<class CType>
ComponentArray<CType>& Scene::getComponentList()
{
	// Doesn't exist yet
	if(componentArrays.find(std::type_index(typeid(CType))) == componentArrays.end())
	{
		componentArrays[std::type_index(typeid(CType))] = new ComponentArray<CType>();
	}

	return *static_cast<ComponentArray<CType>*>(componentArrays[std::type_index(typeid(CType))]);
}

template<class CType>
std::type_index getTypeOf()
{
	return std::type_index(typeid(CType));
}*/

};
NEPHILIM_NS_END
#endif // NephilimScene_h__
