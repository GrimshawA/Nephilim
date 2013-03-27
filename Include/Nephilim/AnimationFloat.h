#ifndef PARABOLA_ANIMATIONFLOAT_H
#define PARABOLA_ANIMATIONFLOAT_H

#include "Platform.h"
#include "Animation.h"
#include "AnimationEasing.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Animation
	\class AnimationFloat
	\brief Animates a float variable with optional easing functions
*/
class PARABOLA_API AnimationFloat : public AnimationInterface{
public:
	AnimationFloat() : AnimationInterface(){
		m_animatedFloat = NULL;
		m_easingFunction = new AnimationEasingQuad();
		m_totalTimeElapsed = 0.f;
	}

	void setTargetValue(float target){
		m_target = target;
	}

	void update(float elapsedTime){
		if(getStatus() == AnimationStates::Playing){
			m_totalTimeElapsed += elapsedTime;
			*m_animatedFloat = m_easingFunction->compute(m_totalTimeElapsed, 0, m_target-0, m_duration);

			//if(m_totalTimeElapsed >= m_duration) stop();
		}
	}

	void setDuration(float length){
		m_duration = length;
	}

	void setVariable(float* var){
		m_animatedFloat = var;
	}

	void setCurrentValue(float value){
		*m_animatedFloat = value;
		m_totalTimeElapsed = 0.f;
	}

private:
	float m_totalTimeElapsed;
	float* m_animatedFloat;
	AnimationEasingFunction* m_easingFunction;
	float m_duration;
	float m_target;
};

PARABOLA_NAMESPACE_END
#endif