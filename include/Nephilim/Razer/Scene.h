#ifndef NephilimScene_h__
#define NephilimScene_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/Entity.h>
#include <Nephilim/Razer/System.h>

#include <vector>
#include <map>
#include <typeindex>

NEPHILIM_NS_BEGIN
namespace rzr {

/**
	\class Scene
	\brief Represents a 3D world
*/
class NEPHILIM_API Scene
{
public:
	Scene();

	/// Create and return a new entity
	Entity createEntity();

	Entity getEntityByIndex(size_t index);

	Entity getEntityById(Int32 id);

	template<class CType>
	ComponentArray<CType>& getComponentList();

	std::vector<EntityInternal> mEntities;
	EntityInternal nextAssignID;

	/// &type_id(component_type) -> ComponentList
	std::map<std::type_index, ComponentList*> componentArrays;

	std::vector<System*> mRegisteredSystems;
};

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
}

};
NEPHILIM_NS_END
#endif // NephilimScene_h__
