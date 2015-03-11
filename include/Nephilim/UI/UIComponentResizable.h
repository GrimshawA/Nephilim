#ifndef NephilimUIComponentResizable_h__
#define NephilimUIComponentResizable_h__

#include <Nephilim/UI/UIController.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentResizable : public UIController
{
public:
	UIComponentResizable();

	void onAttach(Widget* view);

	void onEvent(Event event, Widget* view);

	void onRender(GraphicsDevice* renderer, Widget* view);

	vec2i previousMousePosition;
	bool dragging;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentResizable_h__
