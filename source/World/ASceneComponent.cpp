#include <Nephilim/World/ASceneComponent.h>
#include <Nephilim/World/World.h>

#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

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