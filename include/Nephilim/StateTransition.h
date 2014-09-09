#ifndef NephilimStateTransition_h__
#define NephilimStateTransition_h__

#include <Nephilim/Platform.h>

#include <vector>

NEPHILIM_NS_BEGIN

class StateStack;
class Time;
class Renderer;
class State;
class GameCore;

/**
	\ingroup Core
	\class StateTransition
	\brief Performs a transition animation between two states

	Used together with StateStack and State classes
*/
class NEPHILIM_API StateStackTransition
{
public:
	/// Base construction
	StateStackTransition();

	/// Virtual destructor
	virtual ~StateStackTransition();

	/// Set the duration of the transition effect
	void setDuration(float duration);

	void drawPreviousFrame(Renderer* renderer);
	void drawNextFrame(Renderer* renderer);
	void finish();

	virtual void activate()
	{

	}

	/// Virtual method for updating the transition
	void update(const Time& time);

	virtual void onUpdate(const Time& time);

	virtual void draw(Renderer* renderer);

	bool allowUpdatesA; ///< Set to true to allow the exiting state to update
	bool allowUpdatesB; ///< Set to true to allow the incoming state to update

//private:
	friend class StateStack;
	StateStack* m_stack;

	bool m_finished;

	float m_duration; ///< The total duration of the effect
};

NEPHILIM_NS_END
#endif // NephilimStateTransition_h__