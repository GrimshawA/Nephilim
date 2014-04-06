#include <Nephilim/UI/UIComponentDraggable.h>
#include <Nephilim/UIView.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

UIComponentDraggable::UIComponentDraggable()
: dragging(false)
{

}

void UIComponentDraggable::onAttach(UIView* view)
{

}

void UIComponentDraggable::onEvent(Event event, UIView* view)
{
	if(event.isPointerPressed())
	{
		vec2i mouse_position = event.getPointerPosition();
		if(view->getBounds().contains(mouse_position.x, mouse_position.y))
		{
			Log("Start drag");
			previousMousePosition = mouse_position;
			dragging = true;
		}
	}
	else if(event.isPointerMoved())
	{
		if(dragging)
		{
			vec2i mouse_position = event.getPointerPosition();
			vec2i offset = mouse_position - previousMousePosition;

			view->setPosition(view->getPosition() + vec2(offset.x, offset.y));

			previousMousePosition = mouse_position;
		}
	}
	else if(event.isPointerReleased())
	{
		dragging = false;
	}
}

NEPHILIM_NS_END
