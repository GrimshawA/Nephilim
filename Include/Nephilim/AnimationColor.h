#ifndef PARABOLA_ANIMATIONCOLOR_H
#define PARABOLA_ANIMATIONCOLOR_H

#include "Platform.h"
#include "Animation.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Animation
	\class AnimationColor
	\brief Can animate colors in Animable objects
*/
class PARABOLA_API AnimationColor : public AnimationInterface{
public:
	/// Create the color animation
	AnimationColor();

	/// Update the color of the animable
	void update(float elapsedTime);

private:
	float m_totalTime;
	float m_duration;
};

PARABOLA_NAMESPACE_END
#endif