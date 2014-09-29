#ifndef NephilimRazerEntityInline_h__
#define NephilimRazerEntityInline_h__

/// Implementation of the GetComponent template function to take our Entity wrapper
template<typename T>
T* GetComponent(Entity& e)
{
	ComponentManager* componentManager = e.mScene->getComponentManager<T>();
	Component* component = componentManager->getComponentFromEntity(e.id);
	return static_cast<T*>(component);
}


/// GetMultiComponent is meant to retrieve a list of all the components of a given type bound to the same entity
template<typename T>
std::vector<T*> GetMultiComponent(Entity& e)
{
	std::vector<T*> list;
	return list;
}

template<typename T>
T* CreateComponent(Entity& e)
{
	ComponentManager* componentManager = e.mScene->getComponentManager<T>();
	Component* component = componentManager->createComponentForEntity(e.id);
	return static_cast<T*>(component);
}

/*
template<class CType>
void Entity::addComponent()
{
	CType cp;

	ComponentArray<CType>& components = mScene->getComponentList<CType>();
	components.mComponents.push_back(cp);
	components.mBinding[id] = components.mComponents.size() - 1;

	// Notify systems
	for(std::size_t i = 0; i < mScene->mRegisteredSystems.size(); ++i)
	{
		mScene->mRegisteredSystems[i]->onComponentAdded(getTypeOf<CType>(), (void*)&components.mComponents.back(), this);
	}
}

template<class CType>
CType& Entity::getComponent() const
{
	ComponentArray<CType>& components = mScene->getComponentList<CType>();
	return components.mComponents[ components.mBinding[id] ];
}

template<class CType>
bool Entity::hasComponent() const
{
	ComponentArray<CType>& components = mScene->getComponentList<CType>();
	if(components.mBinding.find(id) == components.mBinding.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

*/
#endif // NephilimRazerEntityInline_h__
