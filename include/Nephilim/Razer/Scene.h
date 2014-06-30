#ifndef NephilimScene_h__
#define NephilimScene_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Razer/Entity.h>
#include <Nephilim/Razer/System.h>

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
	class Layer;

	Scene();

	/// Registers a system to this scene
	void registerSystem(System* system);

	/// Create and return a new entity
	Entity createEntity();

	Entity getEntityByIndex(std::size_t index);

	Entity getEntityById(Int32 id);

	template<class CType>
	ComponentArray<CType>& getComponentList();

	std::vector<EntityInternal> mEntities;
	EntityInternal nextAssignID;

	/// &type_id(component_type) -> ComponentList
	std::map<std::type_index, ComponentList*> componentArrays;

	std::vector<System*> mRegisteredSystems;
	std::vector<Layer>   mLayers;

	class Layer
	{
	public:
		String mName;
		Int32  mLayerID;
	};
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
