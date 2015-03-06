#ifndef NephilimUIComponentDraggable_h__
#define NephilimUIComponentDraggable_h__

#include <Nephilim/UI/UIController.h>

#include <sigc++/sigc++.h>

NEPHILIM_NS_BEGIN

class UIDragEvent;

class NEPHILIM_API UIComponentDraggable : public UIController
{
public:

	sigc::signal<void, const UIDragEvent&> onDragDrop;

	void checkSignals();

	enum MovementAxis
	{
		HorizontalOnly,
		VerticalOnly,
		Both
	};

	UIComponentDraggable();
	UIComponentDraggable(MovementAxis axis);


	void onAttach(UIView* view);

	void onEvent(Event event, UIView* view);

	vec2i previousMousePosition;

	bool dragging;

	MovementAxis mAxis;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentDraggable_h__