#include <Nephilim/StateTransitionFade.h>
#include <Nephilim/Logger.h>
#include <Nephilim/NxMath.h>
#include <Nephilim/Time.h>
#include <Nephilim/Renderer.h>

NEPHILIM_NS_BEGIN

StateTransitionFade::StateTransitionFade()
{
	m_secondPhase = false;
	elapsedTime = 0.f;
	m_duration = 3.f;
	alpha = 0;

	m_rect.setColor(Color::Black);
	m_rect.setSize(1024,768);
	m_rect.setPosition(0,0);

	function.setFunction(AxEasingFunction::QuarticInterpolation);

	lastp = vec2(1024,0);
}

void StateTransitionFade::onUpdate(const Time& time)
{
	elapsedTime += time.asSeconds();

	if(elapsedTime > m_duration)
	{
		finish();
	}
	else
	{
		vec2 p = lastp;
		if(elapsedTime <= (m_duration / 2))
		{
			float currentOffset = function(elapsedTime, 0, 1024, m_duration/2);
			alpha = function(elapsedTime, 0, 255, m_duration/2);
			m_secondPhase = false;
		}
		else
		{
			float currentOffset = function(elapsedTime - m_duration/2 , 0, 1024, m_duration/2);
			alpha = 255 - function(elapsedTime - m_duration/2, 0, 255, m_duration/2);
			m_secondPhase = true;
		}

		m_rect.setColor(Color(0,0,0,alpha));
		lastp = p;
	}
}

void StateTransitionFade::draw(Renderer* renderer)
{
	(elapsedTime <= (m_duration / 2)) ? drawPreviousFrame(renderer) : drawNextFrame(renderer); 
	renderer->draw(m_rect);
}

NEPHILIM_NS_END