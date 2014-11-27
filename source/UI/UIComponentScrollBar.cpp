#include <Nephilim/UI/UIComponentScrollBar.h>
#include <Nephilim/UI/UIView.h>
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
		/*if(dragging)
		{
			vec2i mouse_position = event.getPointerPosition();
			vec2i offset = mouse_position - previousMousePosition;

			float bar_offset_pc = offset.y / view->getSize().y;
			float real_offset = totalHeight * bar_offset_pc;

			view->offsetChildrenPosition(vec2(0.f, -real_offset));

			previousMousePosition = mouse_position;
		}*/
	}
	else if(event.isPointerReleased())
	{
		dragging = false;
	}
	else if (event.type == Event::MouseWheelMoved)
	{
		int scrollWheel = event.mouseWheel.delta * 8;
		view->scrolling_offset.y += scrollWheel;
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

void UIComponentScrollBar::onRender(GraphicsDevice* renderer, UIView* view, const mat4& parentTransform)
{
	RectangleShape backRect(FloatRect(view->size.x - 15.f, 0.f, 15.f, view->size.y), Color(121,121,121));
	renderer->setModelMatrix(parentTransform * backRect.getTransform().getMatrix());
	renderer->draw(backRect);

	float paddleHeight = view->size.y / view->childrenRect().height;
	//Log("size.y = %f", view->size.y);
	//Log("contentHeight = %f", view->childrenRect().height);

	float paddleOffset = (-view->scrolling_offset.y / view->childrenRect().height) * view->size.y;

	RectangleShape backRect2(FloatRect(view->size.x - 15.f + 2.f, 2.f + paddleOffset, 11.f, paddleHeight * view->size.y), Color(21, 21, 21));
	renderer->setModelMatrix(parentTransform * backRect2.getTransform().getMatrix());
	renderer->draw(backRect2);
}

NEPHILIM_NS_END