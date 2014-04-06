#include <Nephilim/UI/UIComponentButton.h>
#include <Nephilim/UIView.h>

NEPHILIM_NS_BEGIN

UIComponentButton::UIComponentButton()
{

}

void UIComponentButton::onAttach(UIView* view)
{
	hovering = false;
}

void UIComponentButton::onEvent(Event event, UIView* view)
{
	if(event.isPointerMoved())
	{
		hovering = view->getBounds().contains(event.getPointerPosition().x, event.getPointerPosition().y);
	}
}

void UIComponentButton::onRender(Renderer* renderer, UIView* view)
{
	if(hovering)
	{
		RectangleShape hoverRect;
		hoverRect.setRect(view->getBounds());
		hoverRect.setColor(Color::Yellow);
		renderer->draw(hoverRect);
	}
}

NEPHILIM_NS_END