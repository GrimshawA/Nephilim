#ifndef NephilimGameState_h__
#define NephilimGameState_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>

#include <vector>

NEPHILIM_NS_BEGIN

class IScript;
class Event;
class StateStack;
class StateStackTransition;
class Time;
class GraphicsDevice;

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

	/// Collection of scripts attached to this state
	std::vector<IScript*> attachedScripts;


public:

	/// Simplest way to call a function in all the attached scripts
	/// No error handling or checking
	void callScriptFunction(const String& name);

	/// Check how many scripts are attached to this state
	std::size_t getNumAttachedScripts();

	/// Creates a default state
	GameState();

	/// Called when there is an event to handle
	virtual void onEvent(const Event &event);

	/// Callback when the state enters the bind list or the stack
	virtual void onAttach();

	/// Callback when the node is activated
	virtual void onActivate();

	/// Callback when the node is deactivated
	virtual void onDeactivate();

	/// Callback when a message is received
	virtual void onMessageReceived(String message);

	/// Callback when data is received
	virtual void onDataReceived(String dataID, void* data);

	/// Get the parent machine of this state
	StateStack* parentMachine();

	/// Tells the parent machine to do a transition animation
	void useTransition(StateStackTransition* transition);

	/// Starts a random transition among the built-in ones
	void useRandomTransition();

	/// Sends a simple message to the binded state
	void sendMessage(const String& bindName, const String& message);

	bool allowsUnderlyingRendering()
	{
		return true;
	}

	/// Attempts to launch a state from the bind list
	bool launchBindedState(const String& stateName);

	/// Finish will inform the state stack this state is done, and should be removed
	void finish();

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
