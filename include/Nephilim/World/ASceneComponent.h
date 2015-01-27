#ifndef NephilimWorldActorASceneComponent_h__
#define NephilimWorldActorASceneComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/ActorComponent.h>
#include <Nephilim/World/CTransform.h>

#include <Nephilim/Foundation/Matrix.h>

NEPHILIM_NS_BEGIN

/**
	\class ASceneComponent
	\brief This is the base class for the Actor components

	The main difference between Component and ActorComponent
	is that ActorComponent has virtual tables due to some
	polymorphic API.
*/
class ASceneComponent : public ActorComponent
{
public:
	mat4 absoluteTransform;

	CTransform t;

	std::vector<ASceneComponent*> attachedComponents;

public:

	/// Update the subtree of transforms
	void updateTransforms();
};

NEPHILIM_NS_END
#endif // NephilimWorldActorASceneComponent_h__
