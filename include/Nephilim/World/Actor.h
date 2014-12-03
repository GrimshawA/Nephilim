#ifndef NephilimActor_h__
#define NephilimActor_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/CTransform.h>
#include <Nephilim/World/CSprite.h>
#include <Nephilim/Math/BBox.h>

NEPHILIM_NS_BEGIN

class ActorComponent
{
public:
	virtual void damn(){}
};

class SceneComponent : public ActorComponent
{
public:
	CTransform t;

	std::vector<SceneComponent*> attachedComponents;

};

class SpriteComponent : public SceneComponent
{
public:
	SpriteComponent()
	{

	}

	CSprite s;
};

class World;

/**
	\class Actor
	\brief Represents an entity in a game world

	This class is used for managing dynamic entities
	in a game world. Usually, vehicles, characters,
	pickups and other props are composed by Actors.

	This is a higher level abstraction than using the World's 
	low level component-based structures.
*/
class NEPHILIM_API Actor
{
private:
	/// World can access private members as he instances Actors
	friend class World;

	/// Pointer to the World instance that created this actor
	World* mWorld = nullptr;

	/// Name of this actor, it doesn't have to be unique
	String mName;

	/// The root component of this Actor
	SceneComponent* root = nullptr;

public:
	/// The array of components on this Actor
	std::vector<ActorComponent*> components;

public:
	/// Get the world instance that created this actor
	World* getWorld();

	/// Get the bounding box of this actor and its contents
	BBox getActorBounds();

	/// Get the transform of this Actor
	/// This is the transform that converts anything in actor space to world space
	CTransform getTransform();

	/// Set a transform for the root
	void setTransform(const CTransform& transform);

	/// Get the position of this Actor
	vec3 getActorLocation();

	/// Destroy this actor
	/// As soon as this function is called, the Actor object may not be used anymore
	void destroy();

	/// Create a new instance of component type T
	template<typename T>
	T* createComponent();

};

/// Create a new instance of component type T
template<typename T>
T* Actor::createComponent()
{
	T* component = new T();
	components.push_back(component);

	if (root == nullptr)
	{
		root = component;
	}

	return component;
}

NEPHILIM_NS_END
#endif // NephilimActor_h__
