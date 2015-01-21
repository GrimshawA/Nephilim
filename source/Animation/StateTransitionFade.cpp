#include <Nephilim/Animation/StateTransitionFade.h>
#include <Nephilim/Math/Math.h>

#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/Time.h>

#include <Nephilim/Graphics/GraphicsDevice.h>

NEPHILIM_NS_BEGIN

StateTransitionFade::StateTransitionFade()
: StateStackTransition()
{
	m_secondPhase = false;
	elapsedTime = 0.f;
	m_duration = 3.f;
	alpha = 255;

	m_stack = NULL;

	this->allowUpdatesA = false;

	m_rect.setColor(Color(0,0,0,0));
	m_rect.setSize(1.f,1.f);
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
		Log("Fade finished");
	}
	else
	{
		vec2 p = lastp;
		if(elapsedTime <= (m_duration / 2))
		{
			float currentOffset = function(elapsedTime, 0, 1024, m_duration/2);
			alpha = function(elapsedTime, 0, 255, m_duration/2);
			m_secondPhase = false;
			//Log("Fading out. Alpha %f", alpha);
		}
		else
		{
			float currentOffset = function(elapsedTime - m_duration/2 , 0, 1024, m_duration/2);
			alpha = 255 - function(elapsedTime - m_duration/2, 0, 255, m_duration/2);
			m_secondPhase = true;
			//Log("Fading in Alpha %f", alpha);
		}

		m_rect.setColor(Color(0,0,0,alpha));
		lastp = p;
	}
}

void StateTransitionFade::draw(GraphicsDevice* renderer)
{
	renderer->clearColorBuffer();

	if(!m_secondPhase)
	{
		drawPreviousFrame(renderer);
	}
	else
	{
		drawNextFrame(renderer);
	}

	renderer->setDepthTestEnabled(false);
	renderer->setBlendingEnabled(true);	
	renderer->setProjectionMatrix(View(0.f, 0.f, 1.f, 1.f).getMatrix());
	renderer->setViewMatrix(mat4::identity);
	renderer->draw(m_rect);
}

NEPHILIM_NS_END