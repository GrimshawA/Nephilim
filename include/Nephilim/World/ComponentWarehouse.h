#ifndef NephilimWorldComponentWarehouse_h__
#define NephilimWorldComponentWarehouse_h__

#include <Nephilim/Platform.h>

#include <map>
#include <typeindex>

NEPHILIM_NS_BEGIN

class ComponentManager;
class DataStream;

/**
	\class ComponentWarehouse
	\brief This class stores component data as efficiently as possible to populate worlds
*/
class NEPHILIM_API ComponentWarehouse
{
public:
	std::map<std::type_index, ComponentManager*> storage;

public:

	template<typename T>
	void initComponentManager(ComponentManager* manager);

	/// Write the data in this warehouse to a stream
	void serialize(DataStream& stream);

	/// Read the warehouse contents from a stream
	void deserialize(DataStream& stream);

};

template<typename T>
void ComponentWarehouse::initComponentManager(ComponentManager* manager)
{
	std::type_index typeindex = std::type_index(typeid(T));

	storage[typeindex] = manager;
}

NEPHILIM_NS_END
#endif // NephilimWorldComponentWarehouse_h__
