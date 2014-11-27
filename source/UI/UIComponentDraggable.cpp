#include <Nephilim/UI/UIComponentDraggable.h>
#include <Nephilim/UI/UIComponentDebug.h>
#include <Nephilim/UI/UIView.h>
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
		if(view->isHit(vec2(mouse_position.x, mouse_position.y)))
		{
			previousMousePosition = mouse_position;
			dragging = true;

			// drag started, create the clone element
			UIView* temp_view = new UIView();
			temp_view->addComponent(new UIComponentDebugColor(Color::Yellow));
			temp_view->setSize(100.f, 100.f);
			temp_view->setPosition(view->getWorldPosition().xy());
			view->getContext()->dragElement = temp_view;
			view->getContext()->dragElementOwner = this;

			Log("Drag-Clone Start");
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

			if (view->getContext()->dragElement && view->getContext()->dragElementOwner == this)
			{
				//view->getContext()->dragElement->setPosition(view->getContext()->dragElement->getPosition() + vec2(offset.x, offset.y) * axisCancellation);
				
				view->getContext()->dragElement->setPosition(event.getPointerPosition().x, event.getPointerPosition().y);

			}
			
			// can't trespass parent
		/*	if(view->getParent() && view->getPosition().x < view->getParent()->getPosition().x)
			{
				view->setPosition(view->getParent()->getPosition().x, view->getPosition().y);
			}
			if(view->getParent() && view->getPosition().x + view->getSize().x > view->getParent()->getPosition().x + view->getParent()->getSize().x)
			{
				view->setPosition(view->getParent()->getPosition().x + view->getParent()->getSize().x - view->getSize().x, view->getPosition().y);
			}*/

			previousMousePosition = mouse_position;
		}
	}
	else if(event.isPointerReleased())
	{
		dragging = false;

		if (view->getContext()->dragElement  && view->getContext()->dragElementOwner == this)
		{
			Log("Drag-Clone Drop");

			UIDragEvent drag;
			drag.dropPosition = event.getPointerPosition();
			drag.dragSource = view;
			drag.dragElement = view->getContext()->dragElement;
			onDragDrop(drag);

			//Log("Emitted on %d", onDragDrop.size());

			delete view->getContext()->dragElement;
			view->getContext()->dragElement = nullptr;
			view->getContext()->dragElementOwner = nullptr;
		}
	}
}

void UIComponentDraggable::checkSignals()
{
	Log("onDragDrop has %d connections", onDragDrop.size());
}

NEPHILIM_NS_END
