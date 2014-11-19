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
	CTransform t;
	return t;
}

NEPHILIM_NS_END