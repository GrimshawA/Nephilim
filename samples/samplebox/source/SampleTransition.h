#ifndef SampleTransition_h__
#define SampleTransition_h__

#include <Nephilim/State.h>
#include <Nephilim/StateTransitionSlider.h>
#include <Nephilim/StateTransitionBlocks.h>
#include <Nephilim/StateTransitionFade.h>
using namespace nx;

class SampleTransition : public State
{
public:
	void onRender(Renderer *renderer)
	{
		renderer->drawDebugCircle(vec2(200,200), 30, vec2(), Color::Red);
		renderer->drawDebugCircle(vec2(300,200), 30, vec2(), Color::Red);
		renderer->drawDebugCircle(vec2(400,200), 30, vec2(), Color::Blue);
		renderer->drawDebugCircle(vec2(500,200), 30, vec2(), Color::Red);
		renderer->drawDebugCircle(vec2(600,200), 30, vec2(), Color::Red);
	}

	void onEvent(const Event &event)
	{
		if(event.key.code == Keyboard::B && event.type == Event::KeyPressed)
		{
			this->finish();
			this->launchBindedState("chooser");
			this->useTransition(new StateTransitionBlocks());
		}

		if(event.key.code == Keyboard::Return && event.type == Event::KeyPressed)
		{		
			this->useTransition(new StateTransitionSlider());
		}

	}
};

#endif // SampleTransition_h__
