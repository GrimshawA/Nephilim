#include <Nephilim/UIScroller.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/RectangleShape.h>
#include <Nephilim/UIView.h>
#include <Nephilim/NxMath.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

void UIComponentScroll::onAttach(UIView* view)
{
	component_id = UIViewComponent::ScrollComponent;
	scrolling = false;
}


void UIComponentScroll::onEvent(Event event, UIView* view)
{
	if(view->m_children.size() == 0)
		return;

	if(event.type == Event::MouseButtonPressed)
	{
		if(view->getBounds().contains(event.mouseButton.x, event.mouseButton.y))
		{
			scrolling = true;
			lastPosition = vec2(event.mouseButton.x, event.mouseButton.y);
		}
	}

	if(event.type == Event::MouseButtonReleased)
	{
		scrolling = false;

		float smallest_distance = fabs(view->m_children[0]->getCenter().y - view->getCenter().y);
		UIView* closestView = view->m_children[0];
		for(size_t i = 0; i < view->m_children.size(); ++i)
		{				
			float dist = fabs(view->m_children[i]->getCenter().y - view->getCenter().y);
			if(dist < smallest_distance)
			{
				smallest_distance = dist;
				closestView = view->m_children[i];
			}
		}

		view->offsetChildrenPosition(vec2(0.f, view->getCenter().y - closestView->getCenter().y));

	}

	if(event.type == Event::MouseMoved)
	{
		vec2 newPosition(event.mouseMove.x, event.mouseMove.y);

		if(scrolling)
		{
			vec2 offset = lastPosition - newPosition;
			offset.x = 0.f;
			offset.y *= -1.f;
			view->offsetChildrenPosition(offset);

			// apply test offset effect
			float biggest_center = view->m_children[0]->getCenter().y;
			float smallest_center = view->m_children[0]->getCenter().y;
			for(size_t i = 0; i < view->m_children.size(); ++i)
			{				
				if(view->m_children[i]->getCenter().y > biggest_center)
				{
					biggest_center = view->m_children[i]->getCenter().y;
				}
				if(view->m_children[i]->getCenter().y < smallest_center)
				{
					smallest_center = view->m_children[i]->getCenter().y;
				}
			}
			// lets ensure its in place. if the bottommost center is on top of the middle, correct
			if(biggest_center < view->getCenter().y)
			{
				float recover_amount = view->getCenter().y - biggest_center;
				view->offsetChildrenPosition(vec2(0.f, recover_amount));
			}
			// lets ensure its in place. if the bottommost center is on top of the middle, correct
			if(smallest_center > view->getCenter().y)
			{
				float recover_amount = smallest_center - view->getCenter().y;
				view->offsetChildrenPosition(vec2(0.f, -recover_amount));
			}
		}

		// track mouse
		lastPosition = vec2(event.mouseMove.x, event.mouseMove.y);
	}
}

UIView* UIComponentScroll::getSelectedView(UIView* view)
{
	if(view->m_children.size() == 0)
		return NULL;

	float smallest_distance = fabs(view->m_children[0]->getCenter().y - view->getCenter().y);
	UIView* closestView = view->m_children[0];
	for(size_t i = 0; i < view->m_children.size(); ++i)
	{				
		float dist = fabs(view->m_children[i]->getCenter().y - view->getCenter().y);
		if(dist < smallest_distance)
		{
			smallest_distance = dist;
			closestView = view->m_children[i];
		}
	}

	return closestView;
}


void UIComponentScroll::onUpdate(const Time& time, UIView* view)
{
	if(view->m_children.size() == 0)
		return;

	// apply test offset effect
	for(size_t i = 0; i < view->m_children.size(); ++i)
	{
		float y_pos = view->m_children[i]->getCenter().y;
		float y_dist = fabs(y_pos - view->getCenter().y);
		float offset = y_dist * 0.3f;

		view->m_children[i]->setCenter(140.f + offset, view->m_children[i]->getCenter().y);
	}
}

void UIComponentScroll::onRender(Renderer* renderer, UIView* view)
{
	RectangleShape backRect(view->getBounds(), Color::Bittersweet);
	renderer->draw(backRect);
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void UIComponentDebugColor::onAttach(UIView* view)
{
	color.r = math::randomInt(0, 255);
	color.g = math::randomInt(0, 255);
	color.b = math::randomInt(0, 255);
	color.a = 255;
}


void UIComponentDebugColor::onRender(Renderer* renderer, UIView* view)
{
	RectangleShape backRect(view->getBounds(), color);
	renderer->draw(backRect);
}


NEPHILIM_NS_END