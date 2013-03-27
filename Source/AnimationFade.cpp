#include <Nephilim/AnimationFade.h>

PARABOLA_NAMESPACE_BEGIN

/// Unitialized animation
AnimationFade::AnimationFade() : m_totalTime(0.f){
	m_function = new AnimationEasingQuad();
	start = end = 0;
	m_duration = 0.f;
};

/// Initialize the animation fully ready to start
AnimationFade::AnimationFade(Animable* animable, int alphaStart, int alphaEnd, float duration): m_totalTime(0.f), start(alphaStart), end(alphaEnd){
	m_function = new AnimationEasingQuad();
	addAnimable(animable);
	m_duration = duration;
};

/// Fresh start, ensure the initial value
void AnimationFade::onBegin(){
	for(unsigned int i = 0; i < m_animables.size(); i++){
		m_animables[i]->animable_set_alpha(start);
	}
};

/// Called when the animation is updating
/// \return MUST return the remaining time not used by the animation
/// This is essential as in a play list of animations, when one finished, the next updates immediately.
float AnimationFade::onUpdate(float elapsedTime){
	if(getStatus() == AnimationStates::Playing){
		m_totalTime += elapsedTime;
		float result =  m_function->compute(m_totalTime, start, end-start, m_duration);
		
		for(unsigned int i = 0; i < m_animables.size(); i++){
			m_animables[i]->animable_set_alpha(static_cast<int>(result));
		}

		if(m_totalTime >= m_duration){
			setStatus(AnimationStates::Stopped);
			// Ensure the end value
			for(unsigned int i = 0; i < m_animables.size(); i++){
				m_animables[i]->animable_set_alpha(end);
			}
			return m_totalTime - m_duration;
		}
		else return elapsedTime;
	}
	else return 0.f;
};

PARABOLA_NAMESPACE_END