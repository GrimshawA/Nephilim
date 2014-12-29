#ifndef NephilimGraphicsParticleSystem_h__
#define NephilimGraphicsParticleSystem_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class ParticleSystem
	\brief Defines a particle-based effect in the game world

	A particle system is a finite set of particles, animated and rendered in particular ways to make interesting effects.
	These can be used to make things like beams, fire, smoke, snow, rain, debris, sparks, magic abilities, ribbon trails and a lot other things.

	A system is essentially an independent simulation of any given effect. The system can be a fire, including flames and smoke; It can be
	a snow field, a tornado, and a lot other things. Multiple emitters are supported to group different effects together.

	Since its rare to have the same particle system in more than one place with a perfectly replicated state (particles are constantly changing
	and being deleted/generated), it almost never makes sense to have a ParticleSystem as a resource being rendered in multiple places. So,
	we will usually have a newly generated ParticleSystem in every place we need one to exist.

	We place particle systems in the world as everything else, through the appropriate component, who will be automatically linked with world
	transforms if applicable.

	The particle systems are also stored as efficiently as possible on runtime, and flagged as static or dynamic, to optimize a little bit,
	in order for operating on all of them with efficiency, for updating inner state, rendering and also to apply outer state changes, like external modifiers.

	Modifiers are force fields and alikes, which will usually influence the behavior of our particles just by being near it. For example,
	a vortex modifier will start attracting all particles nearby into its eye.

	Modifiers can both be bound to a single particle system, but also as a independent component. For example, if a character activates its Attractor component
	while the user casts an attracting spell, it can cause the character to start absorbing surrounding particles and even physical objects.
*/
class NEPHILIM_API ParticleSystem
{
public:

};

NEPHILIM_NS_END
#endif // NephilimGraphicsParticleSystem_h__
