#ifndef NephilimAxBase_h__
#define NephilimAxBase_h__

#include "Platform.h"
#include "AxTarget.h"

#include <list>

NEPHILIM_NS_BEGIN

/**
	\ingroup Animation
	\class AxBase
	\brief Base class for all animations
*/
class NEPHILIM_API AxBase
{
public:

	AxBase()
		: m_looping(false)
		, m_duration(-1.f)
		, m_elapsed(0.f)
	{

	}

	virtual ~AxBase()
	{

	}

	bool isOver()
	{
		return ((m_elapsed > m_duration) && !m_looping);
	}

	/// Step forward the animation
	virtual float update(float delta) = 0;

	std::list<AxTarget*> m_targets;
	float m_duration;
	float m_elapsed;
	bool m_looping;
};

template<class T>
class NEPHILIM_API AxNumeric : public AxBase
{
public:
	AxNumeric(T start, T end, float duration, AxTarget* target = NULL)
		: AxBase()
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
#endif // NephilimAxBase_h__