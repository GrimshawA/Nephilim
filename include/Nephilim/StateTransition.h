#ifndef NephilimStateTransition_h__
#define NephilimStateTransition_h__

#include "Platform.h"

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
class NEPHILIM_API StateTransition
{
public:
	/// Base construction
	StateTransition();

	/// Virtual destructor
	virtual ~StateTransition();

	void drawPreviousFrame(Renderer* renderer);
	void drawNextFrame(Renderer* renderer);
	void finish();

	virtual void activate()
	{

	}

	virtual void update(const Time& time)
	{

	}

	virtual void draw(Renderer* renderer)
	{

	}

private:
	friend class StateStack;
	StateStack* m_stack;

	std::vector<State*> m_futureList;
	bool m_finished;
};

NEPHILIM_NS_END
#endif // NephilimStateTransition_h__