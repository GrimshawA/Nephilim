#ifndef NephilimActor_h__
#define NephilimActor_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/GameObject.h>
#include <Nephilim/World/CTransform.h>
#include <Nephilim/World/CInput.h>
#include <Nephilim/World/CStaticMesh.h>
#include <Nephilim/World/CSprite.h>
#include <Nephilim/World/CColliderBox.h>
#include <Nephilim/World/CSkeletalMesh.h>
#include <Nephilim/Math/BBox.h>

#include <Nephilim/Scripting/IScript.h>

NEPHILIM_NS_BEGIN

class Actor;
class IScript;

class ActorComponent
{
public:
	virtual void damn(){}
};

/**
	\class AScriptComponent
	\brief Allows to attach a scripted behavior to the actor

	These behaviors are used to program gameplay logic into actors.
	The actors are configured usually in a prefab and then spawned into the 
	world, as the engine handles all this natively. Then, one can give behavior to the actor 
	simply by adding a behavior to it. 

	Behaviors can be pretty generic or very problem specific, but they usually 
	focus on the more high-level logic of the game. For example, we can make an
	enemy actor be spawned in the world many times, and they just idle around until
	a script is added to give them behavior. The script may then give each enemy
	the ability to move and manage all animations autonomously, move with pathfinding and so on,
	follow the player etc.

	This is really powerful as it gives life to the game world and not only makes
	characters, vehicles and other assets interesting, but it also helps writing the game
	rules.
*/
class AScriptComponent : public ActorComponent
{
public:
	/// Whether the behavior is enabled
	bool enabled = true;
	
	IScript* _script = nullptr;

	/// This object represents the individual instance of the behavior for this component
	void* object = nullptr;

	void tickScript()
	{
		if (_script)
		{
			_script->callOnObject("void Tick()", object);
			//_script->call("void print2()");
		}
	}
};

class AInputComponent : public ActorComponent, public CInput
{
public:

};

class SceneComponent : public ActorComponent
{
public:
	mat4 absoluteTransform;

	CTransform t;

	std::vector<SceneComponent*> attachedComponents;

public:
	/// Update the subtree of transforms
	void updateTransforms()
	{
		absoluteTransform = t.getMatrix();

		for (std::size_t i = 0; i < attachedComponents.size(); ++i)
		{
			attachedComponents[i]->absoluteTransform = this->absoluteTransform * attachedComponents[i]->t.getMatrix();
		}
	}
};

class SpriteComponent : public SceneComponent
{
public:
	SpriteComponent()
	{

	}

	CSprite s;
};

class SCStaticMesh : public SceneComponent, public CStaticMesh
{
public:
	SCStaticMesh()
	{

	}
};

class NEPHILIM_API ASkeletalMeshComponent : public SceneComponent, public CSkeletalMesh
{
public:

	

	Texture myT;

public:

	void testTexture(const String& name)
	{
		myT.loadFromFile(name);
	}

	void updateAnimation()
	{
		update(Time::fromSeconds(1.f / 60.f));
	}

};

class SCColliderBox : public SceneComponent, public CColliderBox
{
public:

};

/**
	\class ACharacterComponent
	\brief (Actor) Represents a character's position and orientation, a bounding volume and behavior

	Usually, all characters in a game will be instances of the Actor class,
	with a ACharacterComponent as the root component. The physics system will ensure
	validity of this character controller, if there is any.

	It will also conveniently hide networking so the engine takes care of syncing all characters in the simulation.
	Its children components will have their transforms automatically handled to stay relative to the character controller, so
	a character can be easily made to walk around terrain etc, even before we add any final mesh.
*/
class ACharacterComponent : public SceneComponent
{
public:
	void* userData = nullptr;

	sigc::signal<void, Vector3D, Actor*> moving;

public:

	void moveTest(Vector3D displacement, Actor* a)
	{
		moving(displacement, a);
	}
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

	/// Name of this actor, it doesn't have to be unique
	String mName;

	/// The root component of this Actor
	SceneComponent* root = nullptr;

public:
	/// The array of components on this Actor
	std::vector<ActorComponent*> components;

public:

	float X()
	{
		return getActorLocation().x;
	}

	/// Get the world instance that created this actor
	World* getWorld();

	/// Get the bounding box of this actor and its contents
	BBox getActorBounds();

	/// Get the root component
	SceneComponent* getRootComponent();

	/// Set a new root component to this hierarchy
	void setRootComponent(SceneComponent* component);

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

NEPHILIM_NS_END
#endif // NephilimActor_h__
