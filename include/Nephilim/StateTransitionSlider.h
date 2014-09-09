#ifndef NephilimStateTransitionSlider_h__
#define NephilimStateTransitionSlider_h__

#include <Nephilim/Platform.h>
#include "StateTransition.h"
#include "RectangleShape.h"
#include "AxEasing.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Core
	\class StateTransitionSlider
	\brief Native state transition animation
*/
class StateTransitionSlider : public StateStackTransition
{
public:
	/// Constructor
	StateTransitionSlider();

	/// Set the color for the animation
	void setColor(const Color& color);

protected:
	/// Update the transition
	virtual void onUpdate(const Time& time);

	/// Draw the transition
	virtual void draw(Renderer* renderer);


private:
	RectangleShape m_rect;
	bool m_secondPhase;
	AxEasingFunction function;

	vec2 lastp;
	float m_duration;
	float elapsedTime;
	Color m_color;
};

NEPHILIM_NS_END
#endif // NephilimStateTransitionSlider_h__
