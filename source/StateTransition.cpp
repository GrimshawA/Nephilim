#include <Nephilim/StateTransition.h>
#include <Nephilim/StateStack.h>
#include <Nephilim/State.h>

NEPHILIM_NS_BEGIN

StateTransition::StateTransition()
: m_stack(NULL)
, m_finished(false)
{

}

/// Virtual destructor
StateTransition::~StateTransition()
{

}

void StateTransition::setDuration(float duration)
{
	m_duration = duration;
}

void StateTransition::update(const Time& time)
{
	if(allowUpdatesB && m_stack)
	{
		m_stack->updateList(m_futureList, time);
	}
}

void StateTransition::drawPreviousFrame(Renderer* renderer)
{
	if(m_stack)
	{
		m_stack->drawCurrentList(renderer);
	}
}

void StateTransition::drawNextFrame(Renderer* renderer)
{
	if(m_stack)
	{
		// Draw the resulting state stack
		for(size_t i = 0; i < m_futureList.size(); ++i)
		{
			m_futureList[i]->onRender(renderer);

			// In case the state doesn't allow underlying states to render as well just stop here.
			if(!m_futureList[i]->allowsUnderlyingRendering())
				return;
		}
	}
}

void StateTransition::finish()
{
	m_finished = true;
}


NEPHILIM_NS_END