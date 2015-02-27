#ifndef NephilimWorldComponentWarehouse_h__
#define NephilimWorldComponentWarehouse_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Entity.h>
#include <Nephilim/World/ComponentArray.h>

#include <map>
#include <typeindex>
#include <memory>
#include <vector>

NEPHILIM_NS_BEGIN

class ComponentManager;
class DataStream;

/**
	\class ComponentWarehouse
	\brief This class stores component data as efficiently as possible to populate worlds

	This is one of the most crucial parts of the World module, as it will contain all information
	in the level and provide this information to systems for game logic.

	The warehouse can either put the data in the heap or in a pre-allocated allocator,
	but it owns this memory, in a RAII way, and always gets rid of it as it destructs.
*/
class NEPHILIM_API ComponentWarehouse
{
public:
	
	/// Each list of components is known as a component store
	typedef ComponentManager* ComponentStore;

	/// Reference to the actual unique_ptr owning the stuff
	typedef ComponentManager* ComponentStoreRef;

	/// The warehouse has N ready banks, usually immutable
	std::vector<ComponentStore> storage;

	/// This translates a native component typeid into its bank in the array
	std::map<std::type_index, std::size_t> _classTypeToStorageBankMap;

public:

	template<typename T>
	void initComponentManager(ComponentManager* manager);

	template<typename T>
	T& createComponent(Entity e);

	/// Get a component store by its type
	ComponentStoreRef getStore(std::type_index typeindex);

	/// Write the data in this warehouse to a stream
	void serialize(DataStream& stream);

	/// Read the warehouse contents from a stream
	void deserialize(DataStream& stream);
};

template<typename T>
void ComponentWarehouse::initComponentManager(ComponentManager* manager)
{
	std::type_index typeindex = std::type_index(typeid(T));

	storage.push_back(manager);

	_classTypeToStorageBankMap[typeindex] = storage.size() - 1;
}

template<typename T>
T& ComponentWarehouse::createComponent(Entity e)
{
	std::type_index typeindex = std::type_index(typeid(T));

	ComponentStoreRef store = getStore(typeindex);
	if (!store)
	{
		initComponentManager<T>(new ComponentArray<T>());
		store = getStore(typeindex);
	}

	return *static_cast<T*>(store->createComponentForEntity(e));
}

NEPHILIM_NS_END
#endif // NephilimWorldComponentWarehouse_h__
