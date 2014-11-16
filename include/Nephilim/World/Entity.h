#ifndef NephilimRazerEntity_h__
#define NephilimRazerEntity_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Component.h>
#include <Nephilim/World/World.h>

#include <vector>

NEPHILIM_NS_BEGIN

namespace rzr {

/**
	\class Entity
	\brief Utility class to manipulate entities in a scene

	The scene object works independently without a Entity class.
	TEntity is the base type of entities, and that's just an integer.

	This class is a utility wrapper only for doing operations with entities quicker
*/
class NEPHILIM_API Entity
{
public:
	Entity();

	Entity(TEntity e, World& s);


	/// Add a new component to this entity
	template<class CType>
	void addComponent();

	/// Get a component 
	template<class CType>
	CType& getComponent() const;

	template<class CType>
	bool hasComponent() const;

	TEntity id;

	World* mScene;
};

#include <Nephilim/World/Entity.inl>

};
NEPHILIM_NS_END
#endif // NephilimRazerEntity_h__
