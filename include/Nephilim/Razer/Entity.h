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

	entity_id_type id;

	Scene* mScene;
};

template<class CType>
void Entity::addComponent()
{

}

template<class CType>
CType& Entity::getComponent() const
{
	CType c;
	return c;
}

};
NEPHILIM_NS_END
#endif // NephilimRazerEntity_h__
