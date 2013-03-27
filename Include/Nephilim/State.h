#ifndef PARABOLA_STATEMACHINENODE_H
#define PARABOLA_STATEMACHINENODE_H

#include "Platform.h"
#include "Strings.h"
#include "ReferenceCountable.h"
#include "Clock.h"

PARABOLA_NAMESPACE_BEGIN

class StateStack;
class Renderer;
class Event;

/**
		\ingroup Core
		\class StateMachineNode
		\brief Represents a game state such as a pause screen or the game itself.

		This class is reference counted. 
		When the state is created, it has 0 references.
		As soon as the state enters the machine, it goes up to 1 reference.
		When the machine is destroyed, it will destroy all nodes that didn't have the same number of GetState and RemoveReference()

		If you wish to delete the node yourself, use AddReference() as soon as you create it.
*/
class PARABOLA_API State : public RefCountable{
public:
		/// Creates a default state
		State();

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

		/// Sends a simple message to the binded state
		void sendMessage(const String& bindName, const String& message);


		/// Attempts to launch a state from the bind list
		bool launchBindedState(const String& stateName);

		/// Finish will inform the state stack this state is done, and should be removed
		void finish();

		/// Delivers an event to the state
		/// If returns true, it will be propagated to the rest of the stack
		/// Otherwise it will remain under this.
		virtual bool onEvent(Event &event);

		/// Tells the state how much time it should update itself
		/// Must return false if updating lesser states is not wanted
		/// Returning true will update other stack states.
		virtual bool onUpdate(Time &time);

		/// Draws the state with the current renderer
		/// If returns true, other states in the stack will be rendered
		/// Otherwise this state has exclusivity over drawing
		virtual bool onDraw(Renderer *renderer);

		StateStack *m_parent;

	private:
		
		friend class StateStack;

		int RefCount;

		bool m_scheduledRemoval;
	};

PARABOLA_NAMESPACE_END
#endif