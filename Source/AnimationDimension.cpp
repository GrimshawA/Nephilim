#include "Nephilim/AnimationDimension.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN
/// Construct the position animation
AnimationDimension::AnimationDimension(){
		m_duration = 0.f;
		m_function = new AnimationEasingQuad();
		//((AnimationEasingQuad*)myFunction)->easeOut = false;
};

/// Fresh start, ensure the initial value
void AnimationDimension::onBegin(){
	/// TODO
	if(m_animables.size() > 0){
		m_start = m_animables[0]->animable_get_size();
	}

	for(unsigned int i = 0; i < m_animables.size(); i++){
		m_animables[i]->animable_set_size(m_start.x, m_start.y);
	}
};

/// Called when the animation is updating
/// \return MUST return the remaining time not used by the animation
/// This is essential as in a play list of animations, when one finished, the next updates immediately.
float AnimationDimension::onUpdate(float elapsedTime){
	if(getStatus() == AnimationStates::Playing){
		m_totalElapsedTime += elapsedTime;
		float resultx =  m_function->compute(m_totalElapsedTime, m_start.x, m_end.x-m_start.x, m_duration);
		float resulty =  m_function->compute(m_totalElapsedTime, m_start.y, m_end.y-m_start.y, m_duration);


		//cout<<"Data: "<<resultx<<" : "<<m_start.x<<endl;
		for(unsigned int i = 0; i < m_animables.size(); i++){
			m_animables[i]->animable_set_size(resultx, resulty);
		}

		if(m_totalElapsedTime >= m_duration){
			setStatus(AnimationStates::Stopped);
			// Ensure the end value
			for(unsigned int i = 0; i < m_animables.size(); i++){
				m_animables[i]->animable_set_size(m_end.x, m_end.y);
			}
			return m_totalElapsedTime - m_duration;
		}
		else return elapsedTime;
	}
	else return 0.f;
};

/// Set the destination for this animation
void AnimationDimension::setDestination(float x, float y){	
	m_end.x = x;
	m_end.y = y;
};

/// Set the duration
void AnimationDimension::setDuration(float duration){
	m_duration = duration;
};


/// Update method
void AnimationDimension::update(float elapsedTime){
	/*if(myStart == myDestination){
		stop();
	}
	else{
		totalTime += elapsedTime;
		if(totalTime >= myDuration){
			myStart = myDestination;
			m_animables[0]->animable_set_size(myDestination.x,myDestination.y);

		}

		float calc_x = myFunction->compute(totalTime, myStart.x, myDestination.x - myStart.x, myDuration);
		float calc_y = myFunction->compute(totalTime, myStart.y, myDestination.y - myStart.y, myDuration);


		m_animables[0]->animable_set_size(calc_x,calc_y);
		//std::cout<<"t "<<totalTime<<std::endl;
	}*/
};

NEPHILIM_NS_END
