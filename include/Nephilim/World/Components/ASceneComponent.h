#ifndef NephilimWorldActorASceneComponent_h__
#define NephilimWorldActorASceneComponent_h__

#include <Nephilim/World/Component.h>

#include <Nephilim/Foundation/Transform.h>
#include <Nephilim/Foundation/Matrix.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class ASceneComponent
	\brief This is the base class for the Actor components

	The main difference between Component and ActorComponent
	is that ActorComponent has virtual tables due to some
	polymorphic API.
*/
class ASceneComponent : public Component
{
public:
	mat4 absoluteTransform;

	Transform t;

	std::vector<ASceneComponent*> attachedComponents;

public:

	/// Set this component position, relative to its parent's origin
	void setPosition(float x, float y, float z);

	/// Update the subtree of transforms
	void updateTransforms();
};

NEPHILIM_NS_END
#endif // NephilimWorldActorASceneComponent_h__
