#ifndef NephilimAnimationBase_h__
#define NephilimAnimationBase_h__

#include <Nephilim/Platform.h>
#include "AxTarget.h"

#include <list>
#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class Animation
	\brief Base class for all animations
*/
class NEPHILIM_API Animation
{
public:
	/// Default initialization
	Animation();

	/// Initialize with a duration
	Animation(float duration);

	/// Destructor
	virtual ~Animation();

	/// Attempts to deduce initial animation parameters by looking at the targets
	virtual void deduceInitialParameters();

	/// Add a new target for animation
	virtual void addTarget(AxTarget* target);

	/// Get the number of targets
	int getTargetCount();

	/// By default isOver returns true if the elapsed time is bigger than the duration of the animation and it is not looping
	virtual bool isOver();

	/// Get the duration of the animation
	virtual float getDuration();

	/// Step forward the animation
	virtual float update(float delta)
	{
		return 0.f;
	}

	typedef std::list<AxTarget*>::iterator TargetIterator;

protected:

	std::list<AxTarget*> m_targets;
	float m_duration;
	float m_elapsed;
	bool m_looping;
};

template<class T>
class NEPHILIM_API AxNumeric : public Animation
{
public:
	AxNumeric(T start, T end, float duration, AxTarget* target = NULL)
		: Animation()
	{
		m_duration = duration;
		m_start = start;
		m_end = end;

		if(target)
		{
			m_targets.push_back(target);
		}
	}

	~AxNumeric()
	{
//		printf("AxNumeric destroyed.\n");
	}

	float update(float delta)
	{
		//printf("AxNumeric step: %f\n", m_elapsed);

/**		AnimationEasingLinear* easing = new AnimationEasingLinear;

		if(m_targets.size() > 0)
			m_targets[0]->axSetNumber<T>(easing->compute(m_elapsed, m_start, m_end-m_start, m_duration));
		m_elapsed += delta;*/
		return 0.f;
	}

	T m_start;
	T m_end;
};

NEPHILIM_NS_END
#endif // NephilimAnimationBase_h__
