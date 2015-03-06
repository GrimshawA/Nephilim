#ifndef NephilimWorldCharacterComponent_h__
#define NephilimWorldCharacterComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/ASceneComponent.h>

#include <sigc++/sigc++.h>

NEPHILIM_NS_BEGIN

class World;
class Actor;

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
class ACharacterComponent : public ASceneComponent
{
public:
	void* userData = nullptr;

	sigc::signal<void, Vector3D, Actor*> moving;

public:

	void moveTest(Vector3D displacement, Actor* a);
};

NEPHILIM_NS_END
#endif // NephilimWorldCharacterComponent_h__
