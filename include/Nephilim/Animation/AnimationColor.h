#ifndef PARABOLA_ANIMATIONCOLOR_H
#define PARABOLA_ANIMATIONCOLOR_H

#include <Nephilim/Platform.h>
#include "AnimationInterface.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Animation
	\class AnimationColor
	\brief Can animate colors in Animable objects
*/
class NEPHILIM_API AnimationColor : public AnimationInterface{
public:
	/// Create the color animation
	AnimationColor();

	/// Update the color of the animable
	void update(float elapsedTime);

private:
	float m_totalTime;
	float m_duration;
};

NEPHILIM_NS_END
#endif