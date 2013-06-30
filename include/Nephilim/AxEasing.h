#ifndef NephilimAxEasing_h__
#define NephilimAxEasing_h__

#include "Platform.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Animation
	\class AxEasingFunction
	\brief A functor to one easing function
*/
class NEPHILIM_API AxEasingFunction
{
public:
	/// Enumeration of built-in easing functions
	enum NativeEasingFunction
	{
		LinearInterpolation,
		QuarticInterpolation,
		Other
	};

	/// The default easing function is linear interpolation
	AxEasingFunction();

	/// Construct from a easing type
	AxEasingFunction(NativeEasingFunction function);

	/// Compute a value with the easing function
	float operator()(float elapsedTime, float startValue, float valueInterval, float duration);
	
	/// Choose a built-in easing function
	void setFunction(NativeEasingFunction function);

	/// Function definition for all smoothing functions
	typedef float (*easeFuncPtr)(float,float,float,float); 

	/// Set the easing function as an arbitrary compute function
	void setFunction(easeFuncPtr& funcPtr);

private:
	easeFuncPtr m_easeFunction;  ///< Function pointer to a smoothing function
	NativeEasingFunction m_type; ///< Type identifier for the compute function
};

NEPHILIM_NS_END
#endif // NephilimAxEasing_h__
