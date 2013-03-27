#ifndef PARABOLA_STATEMACHINE_H
#define PARABOLA_STATEMACHINE_H

#include "Platform.h"
#include "StateMachineNode.h"

#include <vector>
#include <map>

PARABOLA_NAMESPACE_BEGIN

	class Renderer;
	class Event;

	/**
		\ingroup Core
		\class StateMachine
		\brief Represents a finite state machine.

		It allows you to create a machine and add states to it, then transition between them.
	*/
	class PARABOLA_API StateMachine{
	public:
		/// Creates an empty state machine
		StateMachine();
		/// Safely destroys all states by sending them a destroy callback
		~StateMachine();

		/// Get the state associated with stateID
		/// Returns NULL if that state doesn't belong to the machine
		/// \note This function may be dangerous to use
		/// That is because you get a base node
		/// pointer which you may then cast to your custom state.
		/// If the returned node isn't of the type you casted it to, you get undefined behavior
		/// Using dynamic_cast is recommended to avoid this kind of problems.
		StateMachineNode* getState(int stateID);

		/// Sets a new state or replaces an existing one
		/// It makes an associated between an int identifier and the actual node
		void setState(int stateID, StateMachineNode* node);

		/// Destroys the state specified
		/// States are reference counted, so it may not be destroyed immediately
		void removeState(int stateID);

		/// Replaces the top of the stack with the new state
		void swapState(int stateID);
		/// Pushes a state into the stack
		void pushState(int stateID);
		/// Pops the top of the stack
		void popState();

		/// Handles a signal received from a state
		/// \todo improvements here
		bool handleSignal(int stateID, bool toReplace);
		
		/// Delivers a String to stateID state
		bool deliverMessage(int stateID, String message);

		/// Delivers a String and a pointer to anything to stateID state
		bool deliverData(int stateID, String dataID, void* data);

		/// Updates the right states 
		void updateStates(Time &time);

		/// Delivers the event to the right events
		void propagateEvent(Event &event);

		/// Draws the right states
		void drawStates(Renderer *renderer);

	private:
		std::map<int, StateMachineNode*> nodes;
		std::vector<StateMachineNode*> nodeStack;		
	};
PARABOLA_NAMESPACE_END
#endif