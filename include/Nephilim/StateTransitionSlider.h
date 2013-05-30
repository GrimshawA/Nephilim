#ifndef NephilimStateTransitionSlider_h__
#define NephilimStateTransitionSlider_h__

#include "Platform.h"
#include "StateTransition.h"
#include "RectangleShape.h"
#include "AxEasing.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Core
	\class StateTransitionSlider
	\brief Native state transition animation
*/
class StateTransitionSlider : public StateTransition
{
public:
	/// Constructor
	StateTransitionSlider();

protected:
	/// Update the transition
	virtual void update(const Time& time);

	/// Draw the transition
	virtual void draw(Renderer* renderer);

private:
	RectangleShape m_rect;
	bool m_secondPhase;
	AxEasingFunction function;

	vec2 lastp;
	float m_duration;
	float elapsedTime;
};

NEPHILIM_NS_END
#endif // NephilimStateTransitionSlider_h__
