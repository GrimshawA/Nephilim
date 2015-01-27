#ifndef NephilimActor_h__
#define NephilimActor_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/GameObject.h>
#include <Nephilim/World/ActorComponent.h>
#include <Nephilim/World/ASceneComponent.h>
#include <Nephilim/World/CTransform.h>
#include <Nephilim/World/CInput.h>
#include <Nephilim/World/CStaticMesh.h>
#include <Nephilim/World/CSprite.h>
#include <Nephilim/World/CColliderBox.h>
#include <Nephilim/World/CSkeletalMesh.h>
#include <Nephilim/Foundation/BBox.h>

#include <Nephilim/Scripting/IScript.h>

NEPHILIM_NS_BEGIN

class Actor;




class SCStaticMesh : public ASceneComponent, public CStaticMesh
{
public:
	SCStaticMesh()
	{

	}
};

class SCColliderBox : public ASceneComponent, public CColliderBox
{
public:

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
class NEPHILIM_API Actor : public GameObject
{
private:
	/// World can access private members as he instances Actors
	friend class World;

	/// Pointer to the World instance that created this actor
	World* mWorld = nullptr;



	/// The root component of this Actor
	ASceneComponent* root = nullptr;

public:
	/// The array of components on this Actor
	std::vector<ActorComponent*> components;

	/// Name of this actor, it doesn't have to be unique
	String mName;

public:

	/// Get the world instance that created this actor
	World* getWorld();

	/// Get the bounding box of this actor and its contents
	BBox getActorBounds();

	/// Get the root component
	ASceneComponent* getRootComponent();

	/// Set a new root component to this hierarchy
	void setRootComponent(ASceneComponent* component);

	/// Update the local components to make sure they are positioned relative
	void computeTransformHierarchy();

	/// Get the transform of this Actor
	/// This is the transform that converts anything in actor space to world space
	CTransform getTransform();

	/// Set a transform for the root
	void setTransform(const CTransform& transform);

	/// Get the position of this Actor
	vec3 getActorLocation();

	/// Set the location of this Actor directly
	void setActorLocation(Vector3D location);

	/// Destroy this actor
	/// As soon as this function is called, the Actor object may not be used anymore
	void destroy();

	/// Create a new instance of component type T
	template<typename T>
	T* createComponent();

	/// Find a component of type T
	/// Returns nullptr if there isn't any
	template<typename T>
	T* searchComponent();
};

/// Create a new instance of component type T
template<typename T>
T* Actor::createComponent()
{
	T* component = new T();
	components.push_back(component);

	/*if (root == nullptr)
	{
		root = component;
	}*/

	return component;
}

/// Find a component of type T
/// Returns nullptr if there isn't any
template<typename T>
T* Actor::searchComponent()
{
	for (std::size_t i = 0; i < components.size(); ++i)
	{
		if (dynamic_cast<T*>(components[i]))
		{
			return static_cast<T*>(components[i]);
		}
	}
	return nullptr;
}

NEPHILIM_NS_END
#endif // NephilimActor_h__
