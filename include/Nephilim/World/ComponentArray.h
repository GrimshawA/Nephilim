#ifndef NephilimRazerComponentArray_h__
#define NephilimRazerComponentArray_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/ComponentManager.h>

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN

/**
	\class ComponentArray
	\brief Array of components, acting as a cache efficient pool of components of one type

	This particular implementation of component manager stores the components
*/
template<typename T>
class ComponentArray : public ComponentManager
{
public:
	/// Get a component by its handle value
	virtual Component* getComponent(const CHandle& handle);

	/// Get the number of components being used (not the amount allocated by the pool)
	virtual std::size_t getInstanceCount();

	virtual Component* getInstance(std::size_t index);

	virtual Component* getComponentFromEntity(TEntity e);

	/// Creates a new component mapped to an entity
	virtual Component* createComponentForEntity(TEntity e);

	/// Get the entity to which the instance belongs to
	virtual TEntity getInstanceEntity(std::size_t index);

	virtual void removeComponentsFromEntity(TEntity e);

	/// Array of components of a single type (Contiguous in memory)
	std::vector<T> mComponents;
	std::vector<TEntity> mComponentOwners; ///< Every component has a owner entity

	/// Maps entity id to its component
	std::map<TEntity, std::size_t> mBinding;
};

template<typename T>
void ComponentArray<T>::removeComponentsFromEntity(TEntity e)
{
	auto it = mComponents.begin();
	auto it2 = mComponentOwners.begin();

	while (it != mComponents.end())
	{
		if (*it2 == e)
		{
			it = mComponents.erase(it);
			it2 = mComponentOwners.erase(it2);
		}
		else
		{
			++it;
			++it2;
		}
	}

	mBinding.erase(e);
}


template<typename T>
Component* ComponentArray<T>::getComponent(const CHandle& handle)
{
	return nullptr;
}

template<typename T>
std::size_t ComponentArray<T>::getInstanceCount()
{
	return mComponents.size();
}

template<typename T>
Component* ComponentArray<T>::getInstance(std::size_t index)
{
	return &mComponents[index];
}

/// Get the entity to which the instance belongs to
template<typename T>
TEntity ComponentArray<T>::getInstanceEntity(std::size_t index)
{
	for (std::map<TEntity, std::size_t>::iterator it = mBinding.begin(); it != mBinding.end(); ++it)
	{
		if (it->second == index)
		{
			return it->first;
		}
	}

	return 0;
}


template<typename T>
Component* ComponentArray<T>::getComponentFromEntity(TEntity e)
{
	std::map<TEntity, std::size_t>::iterator it = mBinding.find(e);
	if (it != mBinding.end())
	{
		return &mComponents[it->second];
	}
	else
	{
		return nullptr;
	}
}

template<typename T>
Component* ComponentArray<T>::createComponentForEntity(TEntity e)
{
	T component;
	mComponents.push_back(component);
	mComponentOwners.push_back(e);
	mBinding[e] = mComponents.size() - 1;
	return &mComponents[mComponents.size() - 1];
}

NEPHILIM_NS_END
#endif // NephilimRazerComponentArray_h__
