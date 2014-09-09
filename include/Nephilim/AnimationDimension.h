#ifndef PARABOLA_ANIMATIONDIMENSION_H
#define PARABOLA_ANIMATIONDIMENSION_H

#include <Nephilim/Platform.h>
#include "Vectors.h"
#include "AnimationInterface.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Animation
	\class AnimationDimension
	\brief Animates a transformable object from dimension A to B

*/
class NEPHILIM_API AnimationDimension : public AnimationInterface{
public:
	/// Construct the position animation
	AnimationDimension();

	/// Set the destination for this animation
	void setDestination(float x, float y);

	/// Set the duration
	void setDuration(float duration);

	/// Update method
	void update(float elapsedTime);

	/// Fresh start, ensure the initial value
	void onBegin();

	/// Called when the animation is updating
	/// \return MUST return the remaining time not used by the animation
	/// This is essential as in a play list of animations, when one finished, the next updates immediately.
	virtual float onUpdate(float elapsedTime);

private:
	Vec2f m_start;
	Vec2f m_end;
	float m_duration;

	AnimationEasingFunction *m_function;
};

NEPHILIM_NS_END
#endif