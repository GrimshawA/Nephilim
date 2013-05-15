#include "Nephilim/AnimationGroupSequential.h"
#include "Nephilim/Logger.h"

NEPHILIM_NS_BEGIN

/// Default construction
AnimationGroupSequential::AnimationGroupSequential(){
	m_index = 0;
};

/// Called to trigger the start of this animation
void AnimationGroupSequential::play(){
	// Restart if stopped
	if(getStatus() == AnimationStates::Stopped){
		m_index = 0;
		if(m_animations.size() > 0){
			m_animations[m_index]->setStatus(AnimationStates::Playing);
			m_animations[m_index]->onBegin();
		}
	}
	
	// Set as playing
	setStatus(AnimationStates::Playing);
	onBegin();
};

/// Called when the animation is updating
/// \return MUST return the remaining time not used by the animation
/// This is essential as in a play list of animations, when one finished, the next updates immediately.
float AnimationGroupSequential::onUpdate(float elapsedTime){
	if(getStatus() == AnimationStates::Stopped) return elapsedTime;

	//PRINTLOG("sf", "TIME: %f\n", elapsedTime);

	while((elapsedTime > 0.f) && (m_index < m_animations.size())){
		elapsedTime -= m_animations[m_index]->onUpdate(elapsedTime);
		if(m_animations[m_index]->getStatus() == AnimationStates::Stopped){

			m_index++;

			if(m_index < m_animations.size()){
				m_animations[m_index]->setStatus(AnimationStates::Playing);
				m_animations[m_index]->onBegin();
			}
			else{
				// Nothing else to play now
				setStatus(AnimationStates::Stopped);
				onEnd();
			}

		}
	}

	return std::max<float>(elapsedTime, 0.f);
};

NEPHILIM_NS_END