#ifndef PARABOLA_STATEMACHINE_H
#define PARABOLA_STATEMACHINE_H

#include "Platform.h"
#include "State.h"

#include <vector>
#include <map>

PARABOLA_NAMESPACE_BEGIN

	struct StateStackOperation
	{
		enum Type
		{
			Erase = 0,
			Add
		};

		Type type;
		State* obj;
	};

class Renderer;
class Event;
class GameCore;

/**
		\ingroup Core
		\class StateMachine
		\brief Represents a finite state machine.

		It allows you to create a machine and add states to it, then transition between them.
*/
class PARABOLA_API StateStack{
public:
	/// Creates an empty state machine
	StateStack();

	/// Safely destroys all states by sending them a destroy callback
	~StateStack();

	/// Adds state to immediate execution
	void add(State* state);

	/// Adds a state to the waiting list
	void addWaiting(State* state);

	/// Checks if the stack is empty and if so adds a state from the wait list
	void processWaitList();

	/// Updates the right states 
	void updateStates(Time &time);

	/// Delivers the event to the right events
	void propagateEvent(Event &event);

	/// Draws the right states
	void drawStates(Renderer *renderer);

	int getActiveStateCount();

	/// Bind a new state to the list
	/// Returns false if the name was already taken
	bool bind(const String& name, State* state);

	/// Processes the list of changes to the stack
	void applyChanges();

	/// Erase a state
	void erase(State* state);

	/// Get the parent game, if any
	GameCore* getParentGame();

	/// Get a state or NULL
	State* getBinding(const String& name);

	GameCore* m_parent;

private:
	std::vector<State*> m_activeList; ///< The list of currently active states
	std::vector<State*> m_waitList; ///< The list of states waiting to become active
	std::map<String, State*> m_bindList; ///< The list of binded states, that "live" under the stack

	std::vector<StateStackOperation> m_pendingOperations; ///< The list of pending operations

	bool m_stackLock;
};

class ASEngine;
bool registerStateStack(ASEngine* engine);

PARABOLA_NAMESPACE_END
#endif