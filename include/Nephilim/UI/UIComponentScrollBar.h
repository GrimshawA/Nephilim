#ifndef NephilimUIComponentScrollBar_h__
#define NephilimUIComponentScrollBar_h__

#include <Nephilim/Platform.h>
#include <Nephilim/RectangleShape.h>
#include <Nephilim/UIComponent.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentScrollBar : public UIViewComponent
{
public:
	UIComponentScrollBar();

	void onAttach(UIView* view);

	void onUpdate(const Time& time, UIView* view);

	void onEvent(Event event, UIView* view);

	void onRender(Renderer* renderer, UIView* view);

	vec2i previousMousePosition;
	RectangleShape scrollBarPaddle;
	bool dragging;

	float totalHeight;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentScrollBar_h__