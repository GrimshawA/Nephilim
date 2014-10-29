#ifndef NephilimRazerComponentArray_h__
#define NephilimRazerComponentArray_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/ComponentManager.h>

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN
namespace rzr {

/**
	\class ComponentArray
	\brief Array of components, acting as a cache efficient pool of components of one type

	This particular implementation of component manager stores the components
*/
template<typename T>
class ComponentArray : public ComponentManager
{
public:


	/// Get the number of components being used (not the amount allocated by the pool)
	virtual std::size_t getInstanceCount();

	virtual Component* getInstance(std::size_t index);

	virtual Component* getComponentFromEntity(TEntity e);

	/// Creates a new component mapped to an entity
	virtual Component* createComponentForEntity(TEntity e);

	/// Get the entity to which the instance belongs to
	virtual TEntity getInstanceEntity(std::size_t index);

	/// Array of components of a single type (Contiguous in memory)
	std::vector<T> mComponents;

	/// Maps entity id to its component
	std::map<TEntity, std::size_t> mBinding;
};

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
	mBinding[e] = mComponents.size() - 1;
	return &mComponents[mComponents.size() - 1];
}

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentArray_h__
