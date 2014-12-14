#ifndef NephilimGameState_h__
#define NephilimGameState_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>

#include <vector>

NEPHILIM_NS_BEGIN

class IScript;
class Event;
class GameStateBatch;
class StateStack;
class StateStackTransition;
class Time;
class GraphicsDevice;
class GameCore;

/**
	\class GameState
	\brief Manage the life cycle of an individual state within a game

	This is meant to assist managing a subset of the game, 
	encapsulated in its own class. The class can be inherited for
	implementing its custom behaviors or just scripted.
*/
class NEPHILIM_API GameState
{
public:

	GameCore* mGame = nullptr;

	/// Collection of scripts attached to this state
	std::vector<IScript*> attachedScripts;


public:

	/// Creates a default state
	GameState();

	/// Push a state batch down the stack
	void triggerBatch(const GameStateBatch& batch);

	/// Simplest way to call a function in all the attached scripts
	/// No error handling or checking
	void callScriptFunction(const String& name);

	/// Check how many scripts are attached to this state
	std::size_t getNumAttachedScripts();



	/// Called when there is an event to handle
	virtual void onEvent(const Event &event);

	/// Callback when the state enters the bind list or the stack
	virtual void onAttach();

	/// Callback when the state came into activation (may have animation running for some time still)
	/// But should be prepared for rendering frames from here on.
	virtual void onActivate();

	/// Callback when the state is live and has all ownership of the application flow
	virtual void onLive();

	/// Callback when the node is deactivated
	virtual void onDeactivate();

	/// Callback when a message is received
	virtual void onMessageReceived(String message);

	/// Callback when data is received
	virtual void onDataReceived(String dataID, void* data);

	/// Get the parent machine of this state
	StateStack* parentMachine();

	/// Sends a simple message to the binded state
	void sendMessage(const String& bindName, const String& message);

	/// Get the game object that is running this state
	GameCore& getGame();

	bool allowsUnderlyingRendering()
	{
		return true;
	}

	/// Tells the state how much time it should update itself
	/// Must return false if updating lesser states is not wanted
	/// Returning true will update other stack states.
	virtual void onUpdate(const Time &time);

	/// Draws the state with the current renderer
	/// If returns true, other states in the stack will be rendered
	/// Otherwise this state has exclusivity over drawing
	virtual bool onDraw(GraphicsDevice *renderer);

	/// Draw the state
	virtual void onRender(GraphicsDevice* renderer);

	StateStack *m_parent;

	String mName; /// States can have names

private:
	friend class StateStack;

	bool m_letEventsThrough;

	int RefCount;

	bool m_scheduledRemoval;
};

NEPHILIM_NS_END
#endif // NephilimGameState_h__
