#ifndef PARABOLA_ANIMATIONFADE_H
#define PARABOLA_ANIMATIONFADE_H

#include "Platform.h"
#include "AnimationInterface.h"
#include "AnimationEasing.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API AnimationFade : public AnimationInterface{
public:
	/// Unitialized animation
	AnimationFade();

	/// Initialize the animation fully ready to start
	AnimationFade(Animable* animable, int alphaStart, int alphaEnd, float duration);

	/// Fresh start, ensure the initial value
	void onBegin();

	/// Called when the animation is updating
	/// \return MUST return the remaining time not used by the animation
	/// This is essential as in a play list of animations, when one finished, the next updates immediately.
	virtual float onUpdate(float elapsedTime);

private:
	/// The function that animates the fade
	AnimationEasingFunction* m_function;

	/// Total time since animation start
	float m_totalTime;

	/// Total duration of the animation
	float m_duration;

	/// Start of the alpha value
	int start;

	/// End of the alpha value
	int end;
};

PARABOLA_NAMESPACE_END
#endif // PARABOLA_ANIMATIONFADE_H