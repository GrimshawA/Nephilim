#ifndef NephilimGameStateMachine_h__
#define NephilimGameStateMachine_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN

class Time;
class GameState;
class StateStackTransition;
class GraphicsDevice;
class Event;
class GameCore;

/**
	\class GameStateBatch
	\brief Configuration of the stack state, for transitioning

	By configuring a state batch structure and pushing it to the stack,
	it will activate the exact states ordered and do this with an animated transition if needed.
*/
class GameStateBatch
{
public:

	struct StateUnit
	{
		bool       nameBased; ///< otherwise its object based
		GameState* object;    ///<
		String     name;      ///<
	};

	std::vector<StateUnit> orderedGameStates;

	/// An animation currently being played to transition between nodes in the FSM
	/// When the user sends a signal to transit from node A to node B (current to future state lists)
	/// and he specifies an animation too, it will play autonomously for as long as needed
	/// with its own behavior. When it is done, the node B goes live and becomes the current node, but not before.
	/// The moment the animation is destroyed is exactly when the future list goes LIVE.
	StateStackTransition* animation = nullptr;

public:

	/// Push a state by name instead of object
	void push(const String& state)
	{
		StateUnit unit;
		unit.nameBased = true;
		unit.name = state;
		orderedGameStates.push_back(unit);
	}
};

/**
	\ingroup Core
	\class StateStack
	\brief Mechanism to control game states like the pause screen, main menu, etc

	This tool uses a delayed action system. In other words, it does not necessarily apply changes immediately.

	Whenever you manipulate a StateStack object from a regular place, ie, not inside a State object execution,
	you must always call process() to push the pending changes and refresh the state. In the other hand,
	when the stack is being manipulated internally by State*, process() is completely irrelevant and other rules apply.

	State - bool active - when a state is about to be added to execution, it becomes active, and goes inactive once it finishes
*/
class NEPHILIM_API GameStateMachine
{
public:
	/// This container represents an actual stack of active states on top of each other
	typedef std::vector<GameState*> GameStateList;

	/// This stack is the currently active node in the FSM
	GameStateList mCurrentList;

	/// This stack represents the node about to be activated
	GameStateList mFutureList;

	/// Reference to the GameCore instance that owns this stack
	GameCore* mGame = nullptr;

	/// If we are currently transitioning from one FSM state to another, the animation needs to updating
	StateStackTransition* mAnimation;

private:

	/// There is a batch waiting to be handled
	bool batchPending;

	/// The data of the next batch
	GameStateBatch nextBatch;

	/// Table of named states and their objects
	std::map<String, GameState*> mBindingTable;


public:
	/// Creates an empty state machine
	GameStateMachine();

	/// Safely destroys all states by sending them a destroy callback
	~GameStateMachine();

	/// Push a state batch down the stack
	void triggerBatch(const GameStateBatch& batch);

	/// Clear all active states
	void clear();

	/// Check if a given state is currently being executed
	bool isActive(const String& name);

	/// Check if a given state is currently being executed
	bool isActive(GameState* state);
	
	void drawList(std::vector<GameState*>& list, GraphicsDevice* renderer);

	void drawCurrentList(GraphicsDevice* renderer);

	/// Updates the right states 
	void update(Time &time);

	/// Perform a update on the list
	void updateList(std::vector<GameState*>& list, const Time& time);

	/// Delivers the event to the right events
	void pushEvent(const Event &event);

	/// Draws the right states
	void drawStates(GraphicsDevice *renderer);

	int getActiveStateCount();

	/// Bind a new state to the list
	/// Returns false if the name was already taken
	bool bind(const String& name, GameState* state);

	/// Get the parent game, if any
	GameCore* getParentGame();

	/// Get a state or NULL
	GameState* getBinding(const String& name);
	
	friend class StateStackTransition;

};

NEPHILIM_NS_END
#endif // NephilimGameStateMachine_h__