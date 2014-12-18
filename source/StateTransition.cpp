#include <Nephilim/Strings.h>
#include <Nephilim/StateTransition.h>
#include <Nephilim/Game/GameStateMachine.h>
#include <Nephilim/Game/GameState.h>
#include <Nephilim/Logger.h>

#include <cstddef>

NEPHILIM_NS_BEGIN

StateStackTransition::StateStackTransition()
: m_stack(NULL)
, m_finished(false)
{
	Log("=> State transition instanced : %x", this);
}

/// Virtual destructor
StateStackTransition::~StateStackTransition()
{
	Log("=> State transition destroyed : %x", this);
}

void StateStackTransition::setDuration(float duration)
{
	m_duration = duration;
}

void StateStackTransition::update(const Time& time)
{

	//Log("Updating transition %x, stack %x", this, m_stack);

	if(allowUpdatesA && m_stack)
	{
		m_stack->updateList(m_stack->mCurrentList, time);
	}

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

void StateStackTransition::drawPreviousFrame(GraphicsDevice* renderer)
{
	if(m_stack)
	{
		m_stack->drawList(m_stack->mCurrentList, renderer);
	}
}

void StateStackTransition::drawNextFrame(GraphicsDevice* renderer)
{
	if(m_stack)
	{
		for (auto& gs : m_stack->mFutureList)
		{
			gs->onActivate();
		}

		for (auto& gs : m_stack->mCurrentList)
		{
			gs->onDeactivate();
		}

		m_stack->drawList(m_stack->mFutureList, renderer);
	}
}

void StateStackTransition::finish()
{
	m_finished = true;
}

void StateStackTransition::draw(GraphicsDevice* renderer)
{

}

NEPHILIM_NS_END
