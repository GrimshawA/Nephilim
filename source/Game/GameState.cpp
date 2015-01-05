#include <Nephilim/Game/GameState.h>
#include <Nephilim/Game/GameCore.h>
#include <Nephilim/Game/GameStateMachine.h>

#include <Nephilim/Math/Math.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Window.h>
#include <Nephilim/StateTransitionBlocks.h>
#include <Nephilim/StateTransitionSlider.h>
#include <Nephilim/StateTransitionFade.h>

#include <Nephilim/UI/UICanvas.h>
#include <Nephilim/UI/UIWindow.h>

NEPHILIM_NS_BEGIN

GameState::GameState()
: m_scheduledRemoval(false)
, m_letEventsThrough(false)
{
	m_parent = NULL;
}

/// Get the main world
World* GameState::getWorld()
{
	return getGame().getWorld();
}

/// Create a new behavior for this state
void GameState::createBehavior(const String& scriptFile)
{
	GameBehavior behavior;
	behaviors.push_back(behavior);
}

/// No error handling or checking
void GameState::callScriptFunction(const String& name)
{

}

/// Check how many scripts are attached to this state
std::size_t GameState::getNumAttachedScripts()
{
	return 0;
}

void GameState::onEvent(const Event &event)
{

}

void GameState::onUpdate(const Time &time)
{

}

void GameState::onRender(GraphicsDevice* renderer)
{
	// Default will put the UI on screen
	for (std::size_t i = 0; i < getGame().userInterfaceManager.canvasList.size(); ++i)
	{
		UICanvas* c = getGame().userInterfaceManager.canvasList[i];
		
		renderer->setProjectionMatrix(mat4::ortho(0.f, getGame().getWindow()->width(), getGame().getWindow()->height(), 0.f, 1.f, 5000.f));
		c->draw(renderer);
	}
}

/// Push a state batch down the stack
void GameState::triggerBatch(const GameStateBatch& batch)
{
	if (m_parent && m_parent->mFutureList.empty())
	{
		m_parent->triggerBatch(batch);
	}
	else
	{
		Log("Ignoring FSM signal. Already in transition");
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

GameStateMachine* GameState::parentMachine(){
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

/// Handles the events automatically
void GameState::PrimaryEventHandler(const Event& event)
{
	// Pass events to the UI
	for (std::size_t i = 0; i < getGame().userInterfaceManager.canvasList.size(); ++i)
	{
		UICanvas* c = getGame().userInterfaceManager.canvasList[i];

		c->pushEvent(event);
	}

	onEvent(event);
}

NEPHILIM_NS_END