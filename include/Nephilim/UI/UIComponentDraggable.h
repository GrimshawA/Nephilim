#ifndef NephilimUIComponentDraggable_h__
#define NephilimUIComponentDraggable_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UIComponent.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentDraggable : public UIViewComponent
{
public:
	UIComponentDraggable();

	void onAttach(UIView* view);

	void onEvent(Event event, UIView* view);

	vec2i previousMousePosition;

	bool dragging;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentDraggable_h__