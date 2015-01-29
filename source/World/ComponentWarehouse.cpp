#include <Nephilim/World/ComponentWarehouse.h>

NEPHILIM_NS_BEGIN

/// Get a component store by its type
ComponentWarehouse::ComponentStoreRef ComponentWarehouse::getStore(std::type_index typeindex)
{
	auto it = _classTypeToStorageBankMap.find(typeindex);

	// No store yet, create one
	if (it == _classTypeToStorageBankMap.end())
	{
		return nullptr;
	}
	else
	{
		auto ref = storage[it->second];
		return ref;
	}
}

/// Write the data in this warehouse to a stream
void ComponentWarehouse::serialize(DataStream& stream)
{

}

/// Read the warehouse contents from a stream
void ComponentWarehouse::deserialize(DataStream& stream)
{

}

NEPHILIM_NS_END