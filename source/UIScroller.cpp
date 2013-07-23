#include <Nephilim/UIScroller.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

UIScroller::UIScroller()
: UIControl()
, m_holdingDown(false)
, m_scrollsHorizontally(true)
, m_lowerLimitV(0.f)
, m_currentOffsetV(0.f)
{

}


bool UIScroller::onEventNotification(Event& event)
{
	
	if(event.type == Event::MouseButtonPressed && m_bounds.contains(event.mouseButton.x, event.mouseButton.y))
	{
		m_holdingDown = true;
		m_lastPosition = vec2(event.mouseButton.x, event.mouseButton.y);
	}

	if(event.type == Event::MouseButtonReleased)
		m_holdingDown = false;

	if(event.type == Event::MouseMoved && m_holdingDown)
	{
		// handle the offseting
		vec2 offset = m_lastPosition - vec2(event.mouseMove.x, event.mouseMove.y);
		
		if(!m_scrollsHorizontally)
			offset.x = 0.f;

		offset.y *= -1;

	/*	if(m_currentOffsetV + offset.y < m_lowerLimitV)
		{
			offset.y = m_currentOffsetV - m_lowerLimitV;
		}*/

		m_currentOffsetV += offset.y;

		Log("Curr Offset %f", m_currentOffsetV);

		offsetChildren(offset);

		m_lastPosition = vec2(event.mouseMove.x, event.mouseMove.y);
	}

	if(event.isPointerType())
	{
		vec2i pointCoord = event.getPointerPosition();
		if(!m_bounds.contains(pointCoord.x, pointCoord.y))
		{
			event.type = Event::Count;
		}
	}

	return true;
}

void UIScroller::offsetChildren(vec2 offset)
{
	for(size_t i = 0; i < m_children.size(); ++i)
	{
		m_children[i]->setPosition(m_children[i]->getPosition().x + offset.x, m_children[i]->getPosition().y + offset.y);
	}
}


NEPHILIM_NS_END