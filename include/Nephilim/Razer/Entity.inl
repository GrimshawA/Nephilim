#ifndef NephilimRazerEntityInline_h__
#define NephilimRazerEntityInline_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/Component.h>
#include <Nephilim/Razer/Scene.h>


#include <vector>

NEPHILIM_NS_BEGIN

namespace rzr {

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

};
NEPHILIM_NS_END
#endif // NephilimRazerEntityInline_h__
