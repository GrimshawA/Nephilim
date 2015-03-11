#include <Nephilim/UI/UIComponentResizable.h>
#include <Nephilim/UI/Widget.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

UIComponentResizable::UIComponentResizable()
{
	dragging = false;
}

void UIComponentResizable::onAttach(Widget* view)
{

}

void UIComponentResizable::onEvent(Event event, Widget* view)
{
	if(event.isPointerPressed())
	{
		vec2i mouse_position = event.getPointerPosition();
		if(FloatRect(view->getPosition().x + view->getSize().x - 2, view->getPosition().y, 3, view->getSize().y).contains(mouse_position.x, mouse_position.y))
		{
			Log("Start resize");
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

			//view->setPosition(view->getPosition() + vec2(offset.x, offset.y));
			view->setSize(view->getSize().x + offset.x, view->getSize().y);
			previousMousePosition = mouse_position;
		}		
	}
	else if(event.isPointerReleased())
	{
		dragging = false;
	}
}

void UIComponentResizable::onRender(GraphicsDevice* renderer, Widget* view)
{

}

NEPHILIM_NS_END