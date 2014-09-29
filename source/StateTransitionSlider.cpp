#include <Nephilim/StateTransitionSlider.h>
#include <Nephilim/Logger.h>
#include <Nephilim/NxMath.h>
#include <Nephilim/Time.h>
#include <Nephilim/Graphics/GraphicsDevice.h>

NEPHILIM_NS_BEGIN

StateTransitionSlider::StateTransitionSlider()
{
	m_secondPhase = false;
	elapsedTime = 0.f;
	m_duration = 2.f;

	m_rect.setColor(Color::Black);
	m_rect.setSize(1024,768);
	m_rect.setPosition(1024,0);

	function.setFunction(AxEasingFunction::QuarticInterpolation);

	lastp = vec2(1024,0);
}

void StateTransitionSlider::setColor(const Color& color)
{
	m_color = color;
	m_rect.setColor(color);
}


void StateTransitionSlider::onUpdate(const Time& time)
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
			p.x = 1024 - currentOffset;
			m_secondPhase = false;
		}
		else
		{
			float currentOffset = function(elapsedTime - m_duration/2 , 0, 1024, m_duration/2);
			p.x = currentOffset;
			m_secondPhase = true;
		}

		m_rect.setPosition(p.x,p.y);
		lastp = p;
	}
}

void StateTransitionSlider::draw(GraphicsDevice* renderer)
{
	(elapsedTime <= (m_duration / 2)) ? drawPreviousFrame(renderer) : drawNextFrame(renderer); 
	renderer->setProjectionMatrix(View(0.f, 0.f, 1024.f, 768.f).getMatrix());
	renderer->draw(m_rect);
}

NEPHILIM_NS_END