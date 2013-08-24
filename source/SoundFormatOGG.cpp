#include "Nephilim/AnimationColor.h"

NEPHILIM_NS_BEGIN

/// Create the color animation
AnimationColor::AnimationColor(){
	m_duration = 0.f;
	m_totalTime = 0.f;
};

/// Update the color of the animable
void AnimationColor::update(float elapsedTime){
	if(playing()){
		m_totalTime += elapsedTime;

		if(m_totalTime >= m_duration){
			stop();
			return;
		}

		for(unsigned int i = 0; i < getAnimableCount(); i++){
			Animable* animable = getAnimable(i);
		}
		//update color

	}
};

NEPHILIM_NS_END