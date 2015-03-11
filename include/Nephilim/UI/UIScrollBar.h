#ifndef NephilimUI_ScrollBar_h_
#define NephilimUI_ScrollBar_h_

#include <Nephilim/Platform.h>
#include <Nephilim/UI/Widget.h>

NEPHILIM_NS_BEGIN

/**
	\class UIScrollBar
	\brief Used to spawn scroll bars

	This UIView usually doesn't show in the hierarchy, and instead its hidden under a manager component.
*/
class NEPHILIM_API UIScrollBar : public Widget
{
public:

	/// The scroll bar links to a UIView object to scroll it
	Widget* linkedView = nullptr;

	bool draggingBar = false;
	vec2i lastMouse;

	/// Offset of the draggable paddle to the top of the widget
	/// At 0.0, the paddle is at the highest it can be
	float paddleOffset = 0.f;

	/// Height of the draggable paddle
	/// In local space, cannot exceed the height() of the scroll bar
	float paddleHeight = 0.f;

	enum Orientation
	{
		Vertical,
		Horizontal
	};

public:

	/// Draw the bars themselves
	void onPaint(UIPainter& painter);

	bool onEventNotification(Event& event);

	void onResize();

};

NEPHILIM_NS_END
#endif // NephilimUI_ScrollBar_h_
