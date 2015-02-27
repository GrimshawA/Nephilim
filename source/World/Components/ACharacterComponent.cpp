#include <Nephilim/World/Components/ACharacterComponent.h>

NEPHILIM_NS_BEGIN

void ACharacterComponent::moveTest(Vector3D displacement, Actor* a)
{
	moving(displacement, a);

	if (!userData)
	{
		t.position += displacement;
	}
}

NEPHILIM_NS_END