#include <Nephilim/World/Components/ASceneComponent.h>
#include <Nephilim/World/World.h>

#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

/// Set this component position, relative to its parent's origin
void ASceneComponent::setPosition(float x, float y, float z)
{
	t.position.x = x;
	t.position.y = y;
	t.position.z = z;
}

/// Update the subtree of transforms
void ASceneComponent::updateTransforms()
{
	absoluteTransform = t.getMatrix();

	for (std::size_t i = 0; i < attachedComponents.size(); ++i)
	{
		attachedComponents[i]->absoluteTransform = this->absoluteTransform * attachedComponents[i]->t.getMatrix();
	}
}

NEPHILIM_NS_END