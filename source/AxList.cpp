#include <Nephilim/AxList.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

AxList::~AxList()
{
	std::list<AxBase*>::iterator it = m_animations.begin();
	while( it != m_animations.end())
	{
		delete (*it);
		it++;
	}
}

void AxList::update(float delta)
{
	std::list<AxBase*>::iterator it = m_animations.begin();
	while( it != m_animations.end())
	{
		(*it)->update(delta);

		if((*it)->isOver())
		{
			delete (*it);
			it = m_animations.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void AxList::commit(AxBase* animation)
{
	m_animations.push_back(animation);
}







AnimationStall::AnimationStall(){
	m_duration = 0.f;
	elapsedSinceStart = 0.f;
}

AnimationStall::AnimationStall(float duration){
	m_duration = duration;
	elapsedSinceStart = 0.f;
}

/// Called when the animation is updating
/// \return MUST return the remaining time not used by the animation
/// This is essential as in a play list of animations, when one finished, the next updates immediately.
float AnimationStall::onUpdate(float elapsedTime){
	if(getStatus() == AnimationStates::Playing){
		elapsedSinceStart += elapsedTime;
		//printf("elapsed : %f\n", elapsedSinceStart);

		if(elapsedSinceStart >= m_duration){
			setStatus(AnimationStates::Stopped);
			//printf("Stall ended: %f\n", m_duration);
			//LOG("sddgagasgawgweghw")
			return elapsedSinceStart - m_duration;
		}
		else{
			return elapsedTime; // used all the time
		}
	}
	else return 0.f; // did not need any time
};

NEPHILIM_NS_END