#ifndef PARABOLA_PROGRESSBAR_H
#define PARABOLA_PROGRESSBAR_H

#include "Platform.h"
#include "AnimationFloat.h"
#include "Drawable.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Graphics
	\class ProgressBar
	\brief 
*/
class PARABOLA_API ProgressBar : public Drawable{
public:
	ProgressBar(){
		m_filledWidth = 0.f;
		m_animation.setVariable(&m_filledWidth);
		m_animation.setTargetValue(800);
		m_animation.setDuration(5.f);
		m_animation.play();
	}

	void update(float elapsedTime){
		m_animation.update(elapsedTime);
	}

	void reset(){
		m_animation.setCurrentValue(0.f);
		m_animation.play();
	}

	void onDraw(Renderer* renderer){
		renderer->drawDebugQuad(400,400,0, 800, 50, Color(255,0,0,255));

		renderer->drawDebugQuad(m_filledWidth/2,400,0, m_filledWidth, 50, Color(255,255,0,255));
	}

private:
	float m_filledWidth;
	AnimationFloat m_animation;
};

PARABOLA_NAMESPACE_END
#endif