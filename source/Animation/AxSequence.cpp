#include <Nephilim/AxSequence.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

/// Initializes in ordered mode by default
AxSequence::AxSequence()
: AxBase()
, m_mode(Ordered)
, m_current(0)
{

}

/// Initialize with a sequence mode
AxSequence::AxSequence(SequenceModes mode)
: AxBase()
, m_mode(mode)
, m_current(0)
{

}

/// Initialize with a sequence mode and 0 to 3 initial animations
AxSequence::AxSequence(SequenceModes mode, AxBase *anim1, AxBase *anim2, AxBase* anim3)
: AxBase()
, m_mode(mode)
, m_current(0)
{
	if(anim1) add(anim1);
	if(anim2) add(anim2);
	if(anim3) add(anim3);
}

/// Destroy all animations
AxSequence::~AxSequence()
{
	for(AnimationIterator it = m_animations.begin(); it != m_animations.end(); ++it)
	{
		delete (*it);
	}
}

/// Add a new target for animation
void AxSequence::addTarget(AxTarget* target)
{
	for(AnimationIterator it = m_animations.begin(); it != m_animations.end(); ++it)
	{
		(*it)->addTarget(target);
	}
}

void AxSequence::deduceInitialParameters()
{
	for(AnimationIterator it = m_animations.begin(); it != m_animations.end(); ++it)
	{
		(*it)->deduceInitialParameters();
	}
}

bool AxSequence::isOver()
{
	if(m_mode == Parallel)
	{
		return AxBase::isOver();
	}
	else
	{
		return (AxBase::isOver() && m_current == m_animations.size());
	}
}

float AxSequence::getDuration()
{
	if(m_mode == Ordered)
	{
		float totalDuration = 0.f;
		for(AnimationIterator it = m_animations.begin(); it != m_animations.end(); ++it)
		{
			totalDuration += (*it)->getDuration();
		}

		m_duration = totalDuration;
		return m_duration;
	}
	else
	{
		float higherDuration = 0.f;
		for(AnimationIterator it = m_animations.begin(); it != m_animations.end(); ++it)
		{
			if((*it)->getDuration() > higherDuration)
				higherDuration = (*it)->getDuration();
		}
		m_duration = higherDuration;
		return m_duration;
	}
}

void AxSequence::add(AxBase* animation)
{
	m_animations.push_back(animation);

	getDuration(); // hacky duration update
}

/// Updates the sequence appropriately
float AxSequence::update(float delta)
{
	m_elapsed += delta;

	// Sequential. Update one animation at a time
	if(m_mode == Ordered)
	{
		if(!m_animations.empty() && m_current < m_animations.size())
		{
			m_animations[m_current]->update(delta);

			if(m_animations[m_current]->isOver())
			{
				m_current ++;
				// re-deduce parameters for the new animation
				if(m_current < m_animations.size())
				{
					m_animations[m_current]->deduceInitialParameters();
				}
			}
		}

		// REVISIT: DOESNT WORK CORRECTLY
	}

	else if(m_mode == Parallel)
	{
		for(AnimationIterator it = m_animations.begin(); it != m_animations.end(); ++it)
		{
			(*it)->update(delta);
		}
	}
	
	return 0.f;
}

NEPHILIM_NS_END