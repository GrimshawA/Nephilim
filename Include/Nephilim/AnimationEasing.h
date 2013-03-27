#ifndef PARABOLA_ANIMATION_EASING_H
#define PARABOLA_ANIMATION_EASING_H

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Animation
	\class AnimationEasingFunction
	\brief Base class for different ways of interpolating an animation

	Credits to http://gizma.com/easing/#circ1 for the math on a few easing functions!
*/
class AnimationEasingFunction{
public:
	/// Compute function, which gives the interpolation result
	/// \param t is the total time elapsed of animation
	/// \param b is the initial value of the interpolation
	/// \param c is the range between the initial value and the end value of the interpolation
	/// \param d is the total duration of the animation, expressed in the same unit of t
	virtual float compute(float t,float b,float c,float d) = 0;
};

/**
	\ingroup Animation
	\class AnimationEasingLinear
	\brief Linear function interpolator, no easing
*/
class AnimationEasingLinear : public AnimationEasingFunction{
public:
	/// Implementation of compute for lerp
	float compute(float t,float b,float c,float d);
};

/**
	\ingroup Animation
	\class AnimationEasingQuad
	\brief Quadratic function interpolator, with optional easing in/out
*/
class AnimationEasingQuad : public AnimationEasingFunction{
public:
	/// Construct the default ease in/out settings
	AnimationEasingQuad();

	/// Implementation of compute with a Eased in/out quad function
	float compute(float t,float b,float c,float d);

	/// Choose what is eased, at least one must be true
	bool easeIn, easeOut;
};

/**
	\ingroup Animation
	\class AnimationEasingQuartic
	\brief Quartic function interpolator, with optional easing in/out
*/
class AnimationEasingQuartic : public AnimationEasingFunction{
public:
	/// Implementation of compute with a Eased in/out quad function
	float compute(float t,float b,float c,float d);
};
PARABOLA_NAMESPACE_END
#endif