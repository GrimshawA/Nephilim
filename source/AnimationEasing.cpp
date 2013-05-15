#include "Nephilim/AnimationEasing.h"

NEPHILIM_NS_BEGIN

////////////////////////////////////////////////////////////////////////// Linear easing function
/// Implementation of compute for lerp
float AnimationEasingLinear::compute(float t,float b,float c,float d){
	return c*t/d + b;
};


////////////////////////////////////////////////////////////////////////// Quadratic easing function
/// Construct the default ease in/out settings
AnimationEasingQuad::AnimationEasingQuad(){
	easeIn = true;
	easeOut = true;
};

float AnimationEasingQuad::compute(float t,float b,float c,float d){
	if(easeIn && easeOut){
		t /= d/2;
		if (t < 1) return c/2*t*t + b;
		t--;
		return -c/2 * (t*(t-2) - 1) + b;
	}
	else if(easeIn){
		t /= d;
		return c*t*t + b;
	}
	else{
		t /= d;
		return -c * t*(t-2) + b;
	}
};


////////////////////////////////////////////////////////////////////////// Quartic easing function
/// Implementation of compute with a Eased in/out quad function
float AnimationEasingQuartic::compute(float t,float b,float c,float d){
	t /= d/2;
	if (t < 1) return c/2*t*t*t*t + b;
	t -= 2;
	return -c/2 * (t*t*t*t - 2) + b;
}
NEPHILIM_NS_END
