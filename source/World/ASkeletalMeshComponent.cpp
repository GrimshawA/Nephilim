#include <Nephilim/World/ASkeletalMeshComponent.h>
#include <Nephilim/World/World.h>

#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

void ASkeletalMeshComponent::updateAnimation()
{
	update(Time::fromSeconds(1.f / 60.f));
}

NEPHILIM_NS_END