#ifndef PARABOLA_ANIMATIONSTALL_H
#define PARABOLA_ANIMATIONSTALL_H

#include <Nephilim/Platform.h>
#include "AnimationInterface.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Animation
	\class AnimationStall
	\brief Animation meant to stall only, if you need to skip some time until the next animation.
*/
class NEPHILIM_API AnimationStall : public AnimationInterface{
public:
	AnimationStall();

	AnimationStall(float duration);

	/// Called when the animation is updating
	/// \return MUST return the remaining time not used by the animation
	/// This is essential as in a play list of animations, when one finished, the next updates immediately.
	virtual float onUpdate(float elapsedTime);

	/// The standard update method for animations
	//void update(float elapsedTime);

	float m_duration;
	float elapsedSinceStart;
};

NEPHILIM_NS_END
#endif