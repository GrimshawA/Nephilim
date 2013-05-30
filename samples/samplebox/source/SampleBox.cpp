#include "SampleBox.h"

#include <Nephilim/StateTransitionSlider.h>
#include <Nephilim/StateTransitionBlocks.h>
#include <Nephilim/StateTransitionFade.h>

class SampleChooser : public State
{
public:
	void onRender(Renderer *renderer)
	{
		renderer->drawDebugCircle(vec2(200,200), 30, vec2(), Color::Black);
		renderer->drawDebugCircle(vec2(300,200), 30, vec2(), Color::Red);
		renderer->drawDebugCircle(vec2(400,200), 30, vec2(), Color::Orange);
		renderer->drawDebugCircle(vec2(500,200), 40, vec2(), Color::White);
		renderer->drawDebugCircle(vec2(600,200), 40, vec2(), Color::Blue);
	}

	void onEvent(const Event &event)
	{
		if(event.key.code == Keyboard::B && event.type == Event::KeyPressed)
		{
			this->finish();
			this->launchBindedState("transition");
			this->useRandomTransition();
			Log("Chosen a sample.");
		}
	}
};

void SampleBox::onCreate()
{	
	m_transition = new SampleTransition();

	m_stack.bind("chooser", new SampleChooser());
	m_stack.bind("transition", m_transition);
	m_stack.add("chooser");
	m_stack.process();
}

void SampleBox::onEvent(Event &event)
{
    m_stack.pushEvent(event);
}

void SampleBox::onUpdate(Time time)
{
	m_stack.update(time);
}

void SampleBox::onRender()
{
	getRenderer()->setDefaultViewport();
	getRenderer()->setClearColor(Color::Green);
	getRenderer()->setProjectionMatrix(View(0,0,1024,768).getMatrix());
	m_stack.drawStates(getRenderer());
}
