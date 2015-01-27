#ifndef NephilimWorldAInputComponent_h__
#define NephilimWorldAInputComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/CInput.h>
#include <Nephilim/World/ActorComponent.h>

NEPHILIM_NS_BEGIN

class World;

/**
	\class AInputComponent
	\brief (Actor) Gives the actor the ability to receive input

	Usually, all characters in a game will be instances of the Actor class,
	with a ACharacterComponent as the root component. The physics system will ensure
	validity of this character controller, if there is any.

	It will also conveniently hide networking so the engine takes care of syncing all characters in the simulation.
	Its children components will have their transforms automatically handled to stay relative to the character controller, so
	a character can be easily made to walk around terrain etc, even before we add any final mesh.
*/
class AInputComponent : public ActorComponent, public CInput
{
public:

};

NEPHILIM_NS_END
#endif // NephilimWorldAInputComponent_h__
