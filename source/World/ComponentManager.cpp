#include <Nephilim/Razer/ComponentManager.h>

NEPHILIM_NS_BEGIN

ComponentManager::~ComponentManager()
{
}

/// Get a component from the entity
Component* ComponentManager::getComponentFromEntity(TEntity e)
{
	return nullptr;
}

/// Creates a new component mapped to an entity
Component* ComponentManager::createComponentForEntity(TEntity e)
{
	return nullptr;
}

/// Get the 'index' component in this manager
Component* ComponentManager::getInstance(std::size_t index)
{
	return nullptr;
}

/// Get the entity to which the instance belongs to
TEntity ComponentManager::getInstanceEntity(std::size_t index)
{
	return 0;
}

/// Get the number of components being used (not the amount allocated by the pool)
std::size_t ComponentManager::getInstanceCount()
{
	return 0;
}

NEPHILIM_NS_END