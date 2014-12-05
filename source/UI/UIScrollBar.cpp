#include <Nephilim/UI/UIScrollBar.h>

#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

bool UIScrollBar::onEventNotification(Event& event)
{
	if (event.type == Event::MouseButtonPressed && isHit(vec2(event.mouseButton.x, event.mouseButton.y)))
	{
		// Drag start
		draggingBar = true;
		lastMouse = event.getPointerPosition();
	}
	else if (event.type == Event::MouseButtonReleased)
	{
		draggingBar = false;
	}
	else if (event.type == Event::MouseMoved && draggingBar)
	{
		// Move the paddle in local space, that movement is then translated back to a scrolling factor in the view

		vec2i currMouse = event.getPointerPosition();
		vec2i offset = lastMouse - currMouse;
		lastMouse = currMouse;

		paddleOffset += -offset.y;

		if (paddleOffset <= 0.f)
			paddleOffset = 0.f;

		if (paddleOffset + paddleHeight >= size.y)
			paddleOffset = size.y - paddleHeight;

		Log("paddle offset %f", paddleOffset);

		if (linkedView)
		{
			float scrollToWidgetRatio = linkedView->childrenRect().height / height();
			linkedView->scrolling_offset.y = -paddleOffset * scrollToWidgetRatio;
		}
	}

	return true;
}

void UIScrollBar::onResize()
{
	Log("Something resized me");
}


void UIScrollBar::onPaint(UIPainter& painter)
{
	RectangleShape backRect(FloatRect(0.f, 0.f, size.x, size.y), Color(121, 121, 121));
	painter.graphicsDevice->setModelMatrix(painter.baseMatrix * backRect.getTransform().getMatrix());
	painter.graphicsDevice->draw(backRect);

	if (linkedView)
	{
		paddleHeight = linkedView->size.y / linkedView->childrenRect().height;
		paddleHeight *= size.y;
	}

	RectangleShape backRect2(FloatRect(2.f, 2.f + paddleOffset, size.x - 4.f, paddleHeight - 4.f), Color(21, 21, 21));
	painter.graphicsDevice->setModelMatrix(painter.baseMatrix * backRect2.getTransform().getMatrix());
	painter.graphicsDevice->draw(backRect2);
}

NEPHILIM_NS_END