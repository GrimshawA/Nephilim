#include <Nephilim/Razer/ComponentManager.h>

NEPHILIM_NS_BEGIN
namespace rzr {

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

}

NEPHILIM_NS_END