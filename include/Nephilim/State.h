#ifndef NephilimState_h__
#define NephilimState_h__

#include "Platform.h"
#include "RefCount.h"

NEPHILIM_NS_BEGIN

class String;
class Time;
class StateStack;
class StateTransition;
class Renderer;
class Event;

/**
	\ingroup Core
	\class State
	\brief Holds one state within an application. For example, the pause screen or the menu.
*/
class NEPHILIM_API State : public RefCountable{
public:
	/// Creates a default state
	State();

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
		void useTransition(StateTransition* transition);

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
		virtual bool onDraw(Renderer *renderer);

		/// Draw the state
		virtual void onRender(Renderer* renderer);

		StateStack *m_parent;

private:		
	friend class StateStack;

	bool m_letEventsThrough;

		int RefCount;

		bool m_scheduledRemoval;
};

NEPHILIM_NS_END
#endif // NephilimState_h__