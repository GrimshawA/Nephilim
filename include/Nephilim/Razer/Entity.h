#ifndef NephilimRazerEntity_h__
#define NephilimRazerEntity_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/Component.h>

#include <vector>

NEPHILIM_NS_BEGIN

namespace rzr {




#ifdef RAZER_ENTITY_64
#define entity_id_type Int64
#else
#define entity_id_type Int32
#endif

/**
	\class EntityInternal
	\brief Internal representation of the entity
*/
class NEPHILIM_API EntityInternal
{
public:
	EntityInternal();

	EntityInternal(entity_id_type id);

	entity_id_type mId;
};

class Scene;
/**
	\class Entity
	\brief Reference to an entity
*/
class NEPHILIM_API Entity
{
public:

	/// Add a new component to this entity
	template<class CType>
	void addComponent();

	/// Get a component 
	template<class CType>
	CType& getComponent() const;

	template<class CType>
	bool hasComponent() const;

	entity_id_type id;

	Scene* mScene;
};

template<class CType>
void Entity::addComponent()
{
	CType cp;

	ComponentArray<CType>& components = mScene->getComponentList<CType>();
	components.mComponents.push_back(cp);
	components.mBinding[id] = components.mComponents.size() - 1;

	// Notify systems
	for(size_t i = 0; i < mScene->mRegisteredSystems.size(); ++i)
	{
		mScene->mRegisteredSystems[i]->onComponentAdded(getTypeOf<CType>(), (void*)&components.mComponents.back());
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
#endif // NephilimRazerEntity_h__
