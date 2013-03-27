#ifndef PARABOLA_ANIMATIONSTALL_H
#define PARABOLA_ANIMATIONSTALL_H

#include "Platform.h"
#include "Animation.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Animation
	\class AnimationStall
	\brief Animation meant to stall only, if you need to skip some time until the next animation.
*/
class PARABOLA_API AnimationStall : public AnimationInterface{
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

PARABOLA_NAMESPACE_END
#endif