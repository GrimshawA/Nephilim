#include <Nephilim/Game/GameState.h>

#include <Nephilim/NxMath.h>
#include <Nephilim/StateStack.h>
#include <Nephilim/StateTransitionBlocks.h>
#include <Nephilim/StateTransitionSlider.h>
#include <Nephilim/StateTransitionFade.h>

NEPHILIM_NS_BEGIN

/// Simplest way to call a function in all the attached scripts
/// No error handling or checking
void GameState::callScriptFunction(const String& name)
{

}

/// Check how many scripts are attached to this state
std::size_t GameState::getNumAttachedScripts()
{
	return 0;
}


GameState::GameState()
: m_scheduledRemoval(false)
, m_letEventsThrough(false)
{
	m_parent = NULL;
}

void GameState::onEvent(const Event &event)
{

}

void GameState::onUpdate(const Time &time)
{

}

void GameState::onRender(GraphicsDevice* renderer)
{

}

/// Push a state batch down the stack
void GameState::triggerBatch(const GameStateBatch& batch)
{
	if (m_parent)
	{
		m_parent->triggerBatch(batch);
	}
}

/// Callback when the state is live and has all ownership of the application flow
void GameState::onLive()
{}

void GameState::onActivate()
{}

void GameState::onDeactivate()
{}

void GameState::onAttach()
{}

void GameState::onMessageReceived(String message){

};

void GameState::onDataReceived(String dataID, void* data){

};

/// Get the game object that is running this state
GameCore& GameState::getGame()
{
	return *mGame;
}

StateStack* GameState::parentMachine(){
	return m_parent;
};

/// Sends a simple message to the binded state
void GameState::sendMessage(const String& bindName, const String& message)
{
	if (m_parent)
	{
		GameState* state = m_parent->getBinding(bindName);
		if (state)
		{
			state->onMessageReceived(message);
		}
	}
};

/// Draws the state with the current renderer
/// If returns true, other states in the stack will be rendered
/// Otherwise this state has exclusivity over drawing
bool GameState::onDraw(GraphicsDevice *renderer){
	return true;
};

NEPHILIM_NS_END