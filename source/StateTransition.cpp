#include <Nephilim/StateTransition.h>
#include <Nephilim/StateStack.h>
#include <Nephilim/State.h>
#include <Nephilim/Logger.h>

#include <cstddef>

NEPHILIM_NS_BEGIN

StateStackTransition::StateStackTransition()
: m_stack(NULL)
, m_finished(false)
{

}

/// Virtual destructor
StateStackTransition::~StateStackTransition()
{

}

void StateStackTransition::setDuration(float duration)
{
	m_duration = duration;
}

void StateStackTransition::update(const Time& time)
{
	if(allowUpdatesB && m_stack)
	{
		m_stack->updateList(m_stack->mFutureList, time);
	}

	onUpdate(time);

	if(m_stack->mCurrentList.size() > 0 && m_stack->mFutureList.size() > 0)
	{
		//Log("Transition prev %s next %s", m_stack->mCurrentList[0]->mName.c_str(), m_stack->mFutureList[0]->mName.c_str());

	}
	/*else
		Log("MAN, this is wrong.");*/
}

void StateStackTransition::onUpdate(const Time& time)
{

}

void StateStackTransition::drawPreviousFrame(Renderer* renderer)
{
	if(m_stack)
	{
		m_stack->drawList(m_stack->mCurrentList, renderer);
	}
}

void StateStackTransition::drawNextFrame(Renderer* renderer)
{
	if(m_stack)
	{
		m_stack->drawList(m_stack->mFutureList, renderer);
	}
}

void StateStackTransition::finish()
{
	m_finished = true;

	// When the transition is finished, it commits the future list as the current
	m_stack->mCurrentList = m_stack->mFutureList;
	m_stack->mFutureList.clear();
}

void StateStackTransition::draw(Renderer* renderer)
{

}

NEPHILIM_NS_END
