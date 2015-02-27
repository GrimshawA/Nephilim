#include <Nephilim/Animation/AnimationZ.h>

#include <Nephilim/Foundation/Logging.h>

#include <Nephilim/UI/UIView.h>

NEPHILIM_NS_BEGIN

AnimationZ::AnimationZ(float targetZ, float _duration)
: Animation()
, m_easing(AxEasingFunction::QuarticInterpolation)
{
	_targetZ = targetZ;
	_currentZ = 0.f;

	m_duration = _duration;
}

float AnimationZ::update(float delta)
{
	m_elapsed += delta;

	float c = m_easing(m_elapsed, _currentZ, _targetZ - _currentZ, m_duration);

	//Log("%f of %f", m_elapsed, m_duration);

	setZCallback(c);

	return 0.f;
}


/// Attempts to deduce initial animation parameters by looking at the targets
void AnimationZ::deduceInitialParameters()
{
	if (getTargetCount() > 0)
	{
		_currentZ = ((UIView*)m_targets.front())->position.z;
	}
}

NEPHILIM_NS_END
