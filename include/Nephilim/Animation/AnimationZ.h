#ifndef NephilimAnimationZ_h__
#define NephilimAnimationZ_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Animation/Animation.h>
#include <Nephilim/Animation/AxEasing.h>

#include <sigc++/sigc++.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API AnimationZ : public Animation
{
public:

	float _currentZ;
	float _targetZ;

	sigc::signal<void, float> setZCallback;

	AxEasingFunction m_easing;

public:

	/// Construct with a target Z coordinate
	AnimationZ(float targetZ, float _duration);

	/// Update state of animation
	float update(float delta);

	/// Attempts to deduce initial animation parameters by looking at the targets
	virtual void deduceInitialParameters();
};

NEPHILIM_NS_END
#endif // NephilimAnimationZ_h__