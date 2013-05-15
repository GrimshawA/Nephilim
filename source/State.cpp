#include "Nephilim/State.h"
#include "Nephilim/StateStack.h"
#include "Nephilim/Event.h"

#include <iostream>

NEPHILIM_NS_BEGIN
	State::State() : RefCountable(), m_scheduledRemoval(false) {
		m_parent = NULL;
	};

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
		State* bindedState = m_parent->getBinding(stateName);
		if(bindedState)
		{
			m_parent->add(bindedState);
			return true;
		}
		else return false;
	}
	else return false;
};


	/// Delivers an event to the state
	/// If returns true, it will be propagated to the rest of the stack
	/// Otherwise it will remain under this.
	bool State::onEvent(Event &event){
		return true;
	};

	bool State::onUpdate(Time &time){
		return true;
	};

	/// Draws the state with the current renderer
	/// If returns true, other states in the stack will be rendered
	/// Otherwise this state has exclusivity over drawing
	bool State::onDraw(Renderer *renderer){
		return true;
	};

NEPHILIM_NS_END