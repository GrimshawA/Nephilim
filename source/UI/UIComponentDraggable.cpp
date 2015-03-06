#include <Nephilim/UI/UIComponentDraggable.h>
//#include <Nephilim/UI/UIComponentDebug.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Foundation/Logging.h>

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
//			temp_view->addController(new UIDebugWidget(Color::Yellow));
			temp_view->setSize(100.f, 100.f);
			temp_view->setPosition(view->getWorldPosition().xy());
			view->getCore()->dragElement = temp_view;
			view->getCore()->dragElementOwner = this;

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

			if (view->getCore()->dragElement && view->getCore()->dragElementOwner == this)
			{
				//view->getCore()->dragElement->setPosition(view->getCore()->dragElement->getPosition() + vec2(offset.x, offset.y) * axisCancellation);
				
				view->getCore()->dragElement->setPosition(event.getPointerPosition().x, event.getPointerPosition().y);

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

		if (view->getCore()->dragElement  && view->getCore()->dragElementOwner == this)
		{
			Log("Drag-Clone Drop");

			UIDragEvent drag;
			drag.dropPosition = event.getPointerPosition();
			drag.dragSource = view;
			drag.dragElement = view->getCore()->dragElement;
			onDragDrop(drag);

			//Log("Emitted on %d", onDragDrop.size());

			delete view->getCore()->dragElement;
			view->getCore()->dragElement = nullptr;
			view->getCore()->dragElementOwner = nullptr;
		}
	}
}

void UIComponentDraggable::checkSignals()
{
	Log("onDragDrop has %d connections", onDragDrop.size());
}

NEPHILIM_NS_END
