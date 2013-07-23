#ifndef NephilimStateTransitionBlocks_h__
#define NephilimStateTransitionBlocks_h__

#include "Platform.h"
#include "StateTransition.h"
#include "RectangleShape.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Core
	\class StateTransitionBlocks
	\brief Native state transition animation
*/
class StateTransitionBlocks : public StateTransition
{
public:
	/// Constructor
	StateTransitionBlocks();

	/// Update the transition
	virtual void onUpdate(const Time& time);

	/// Draw the transition
	virtual void draw(Renderer* renderer);

private:
	std::vector<RectangleShape> shapes;
	std::vector<vec2> positions;

	float remainingTime;
	bool m_next;
	float blockSize;
};

NEPHILIM_NS_END

#endif // NephilimStateTransitionBlocks_h__
