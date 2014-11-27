#include <Nephilim/World/Actor.h>
#include <Nephilim/World/World.h>

NEPHILIM_NS_BEGIN

/// Get the world instance that created this actor
World* Actor::getWorld()
{
	return mWorld;
}

/// Destroy this actor
/// As soon as this function is called, the Actor object may not be used anymore
void Actor::destroy()
{
	if (mWorld)
	{
		mWorld->destroyActor(this);
	}
}

/// Get the transform of this Actor
/// This is the transform that converts anything in actor space to world space
CTransform Actor::getTransform()
{
	CTransform transform;
	if (root)
	{
		transform = root->t;
	}
	return transform;
}

/// Set a transform for the root
void Actor::setTransform(const CTransform& transform)
{
	if (root)
	{
		root->t = transform;
	}
}

/// Get the position of this Actor
vec3 Actor::getActorLocation()
{
	return getTransform().position;
}

NEPHILIM_NS_END