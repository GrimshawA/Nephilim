#include <Nephilim/UI/UIComponentScrollBar.h>
#include <Nephilim/UIView.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

UIComponentScrollBar::UIComponentScrollBar()
{
	dragging = false;
}

void UIComponentScrollBar::onAttach(UIView* view)
{

}

void UIComponentScrollBar::onEvent(Event event, UIView* view)
{
	if(event.isPointerPressed())
	{
		vec2i mouse_position = event.getPointerPosition();
		if(scrollBarPaddle.contains(vec2(mouse_position.x, mouse_position.y)))
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

			float bar_offset_pc = offset.y / view->getSize().y;
			float real_offset = totalHeight * bar_offset_pc;

			view->offsetChildrenPosition(vec2(0.f, -real_offset));

			previousMousePosition = mouse_position;
		}		
	}
	else if(event.isPointerReleased())
	{
		dragging = false;
	}
}

void UIComponentScrollBar::onUpdate(const Time& time, UIView* view)
{

	float lowestY = view->m_children[0]->getPosition().y;
	float highestY = view->m_children[0]->getPosition().y + view->m_children[0]->getSize().y;
	for(std::size_t i = 0; i < view->m_children.size(); ++i)
	{
		if(view->m_children[i]->getPosition().y < lowestY)
		{
			lowestY = view->m_children[i]->getPosition().y;
		}

		if(view->m_children[i]->getPosition().y + view->m_children[i]->getSize().y > highestY)
		{
			highestY = view->m_children[i]->getPosition().y + view->m_children[i]->getSize().y;
		}
	}

	//Log("Window %f to %f, Content %f to %f", getPosition().y, getPosition().y + getSize().y, lowestY, highestY);

	float beginPercent = (view->getPosition().y - lowestY) / (highestY  - lowestY);
	float endPercent = (view->getPosition().y + view->getSize().y - lowestY) / (highestY  - lowestY);

	//Log("You are viewing %f pc of the content", beginPercent);

	scrollBarPaddle.setSize(17.f, view->getSize().y * (endPercent-beginPercent));
	scrollBarPaddle.setPosition(view->getPosition().x + view->getSize().y - 17.f, view->getPosition().y + view->getSize().y * beginPercent);
	scrollBarPaddle.setColor(Color::Red);

	totalHeight = highestY - lowestY;
}

void UIComponentScrollBar::onRender(Renderer* renderer, UIView* view)
{
	RectangleShape scrollBarBackground;
	scrollBarBackground.setSize(17.f, view->getSize().y);
	scrollBarBackground.setPosition(view->getPosition().x + view->getSize().y - 17.f, view->getPosition().y);
	scrollBarBackground.setColor(Color::Blue);
	renderer->draw(scrollBarBackground);

	renderer->draw(scrollBarPaddle);
}
NEPHILIM_NS_END