#include <Nephilim/State.h>
#include <Nephilim/Time.h>
#include <Nephilim/Strings.h>
#include "Nephilim/StateStack.h"
#include "Nephilim/Event.h"
#include "Nephilim/NxMath.h"
#include "Nephilim/StateTransitionBlocks.h"
#include "Nephilim/StateTransitionSlider.h"
#include "Nephilim/StateTransitionFade.h"

#include <iostream>

NEPHILIM_NS_BEGIN

State::State()
: RefCountable()
, m_scheduledRemoval(false)
, m_letEventsThrough(false)
{
		m_parent = NULL;
}

void State::onEvent(const Event &event)
{

}

void State::onUpdate(const Time &time)
{
	
}

void State::onRender(Renderer* renderer)
{

}

/// Starts a random transition among the built-in ones
void State::useRandomTransition()
{
	int id = math::randomInt(0, 2);

	switch(id)
	{
	case 0: useTransition(new StateTransitionBlocks()); break;
	case 1: useTransition(new StateTransitionSlider()); break;
	case 2: useTransition(new StateTransitionFade()); break;
	}
}

/// Tells the parent machine to do a transition animation
void State::useTransition(StateTransition* transition)
{
	if(m_parent)
	{
		m_parent->performTransition(transition);
	}
}
	void State::onActivate(){
		
	};

	void State::onDeactivate(){

	};

	/// Callback when the state enters the bind list or the stack
	void State::onAttach()
	{

	};

	void State::onMessageReceived(String message){

	};

	void State::onDataReceived(String dataID, void* data){

	};

StateStack* State::parentMachine(){
	return m_parent;
};



/// Finish will inform the state stack this state is done, and should be removed
void State::finish()
{
	if(m_scheduledRemoval)
	{
		return;
	}
	else
	{
		if(m_parent)
		{
			// schedule this state for erasing
			m_parent->erase(this);
			m_scheduledRemoval = true;
		}
	}
};

/// Sends a simple message to the binded state
void State::sendMessage(const String& bindName, const String& message)
{
	if(m_parent)
	{
		State* state = m_parent->getBinding(bindName);
		if(state)
		{
			state->onMessageReceived(message);
		}
	}
};

/// Attempts to launch a state from the bind list
bool State::launchBindedState(const String& stateName)
{
	if(m_parent)
	{
		m_parent->add(stateName);
	}
	else return false;
};


	/// Draws the state with the current renderer
	/// If returns true, other states in the stack will be rendered
	/// Otherwise this state has exclusivity over drawing
	bool State::onDraw(Renderer *renderer){
		return true;
	};

NEPHILIM_NS_END