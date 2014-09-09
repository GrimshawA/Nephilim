#ifndef NephilimUIComponentResizable_h__
#define NephilimUIComponentResizable_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UI/UIComponent.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentResizable : public UIComponent
{
public:
	UIComponentResizable();

	void onAttach(UIView* view);

	void onEvent(Event event, UIView* view);

	void onRender(Renderer* renderer, UIView* view);

	vec2i previousMousePosition;
	bool dragging;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentResizable_h__
