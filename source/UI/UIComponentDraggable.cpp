#include <Nephilim/UI/UIComponentDraggable.h>
#include <Nephilim/UIView.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

UIComponentDraggable::UIComponentDraggable()
: dragging(false)
{
	mAxis = Both;
}

UIComponentDraggable::UIComponentDraggable(MovementAxis axis)
: dragging(false)
{
	mAxis = axis;
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

			vec2 axisCancellation(0.f, 0.f);
			if(mAxis == Both || mAxis == HorizontalOnly)
				axisCancellation.x = 1.f;
			if(mAxis == Both || mAxis == VerticalOnly)
				axisCancellation.y = 1.f;

			view->setPosition(view->getPosition() + vec2(offset.x, offset.y) * axisCancellation);
			
			// can't trespass parent
			if(view->getParent() && view->getPosition().x < view->getParent()->getPosition().x)
			{
				view->setPosition(view->getParent()->getPosition().x, view->getPosition().y);
			}
			if(view->getParent() && view->getPosition().x + view->getSize().x > view->getParent()->getPosition().x + view->getParent()->getSize().x)
			{
				view->setPosition(view->getParent()->getPosition().x + view->getParent()->getSize().x - view->getSize().x, view->getPosition().y);
			}

			previousMousePosition = mouse_position;
		}
	}
	else if(event.isPointerReleased())
	{
		dragging = false;
	}
}

NEPHILIM_NS_END
