#ifndef NephilimStateTransitionFade_h__
#define NephilimStateTransitionFade_h__

#include "Platform.h"
#include "StateTransition.h"
#include "RectangleShape.h"
#include "AxEasing.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Core
	\class StateTransitionFade
	\brief Native state transition animation
*/
class StateTransitionFade : public StateTransition
{
public:
	/// Constructor
	StateTransitionFade();

protected:
	/// Update the transition
	virtual void onUpdate(const Time& time);

	/// Draw the transition
	virtual void draw(Renderer* renderer);

private:
	RectangleShape m_rect;
	bool m_secondPhase;
	AxEasingFunction function;

	float alpha;
	vec2 lastp;
	float m_duration;
	float elapsedTime;
};

NEPHILIM_NS_END
#endif // NephilimStateTransitionFade_h__
