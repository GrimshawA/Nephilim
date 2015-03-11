#include <Nephilim/UI/UIComponentTouchScroll.h>

#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Graphics/RectangleShape.h>
#include <Nephilim/UI/Widget.h>
#include <Nephilim/Foundation/Math.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN
	/*
UIComponentScroll::UIComponentScroll()
{
	Log("UIComponentScroll()");
}
*/
void UIComponentScroll::onAttach(Widget* view)
{
	component_id = UIController::ScrollComponent;
	scrolling = false;

	view->m_clipChildren = true;

	mScrollsHorizontally = true;
	mScrollsVertically = false;
	mPageBased = true;

	// This code doesn't belong here

	if(mPageBased)
	{
		float offset = 0.f;
		for(std::size_t i = 0; i < view->mChildren.size(); ++i)
		{
			static_cast<Widget*>(view->mChildren[i])->setSize(view->getSize().x, view->getSize().y);
			static_cast<Widget*>(view->mChildren[i])->setPosition(view->getPosition().x + offset, view->getPosition().y);

			offset += view->getSize().x;
		}
	}
}

void UIComponentScroll::onEvent(Event event, Widget* view)
{
	if(view->mChildren.size() == 0)
		return;

	if(event.type == Event::MouseButtonPressed)
	{
		if(view->getRect().contains(event.mouseButton.x, event.mouseButton.y))
		{
			scrolling = true;
			lastPosition = vec2(event.mouseButton.x, event.mouseButton.y);
		}
	}

	if(event.type == Event::MouseButtonReleased)
	{
		scrolling = false;

		float smallest_distance = fabs(static_cast<Widget*>(view->mChildren[0])->getCenter().y - view->getCenter().y);
		Widget* closestView = static_cast<Widget*>(view->mChildren[0]);

		for(std::size_t i = 0; i < view->mChildren.size(); ++i)
		{				
			float dist = fabs(static_cast<Widget*>(view->mChildren[i])->getCenter().y - view->getCenter().y);
			if(dist < smallest_distance)
			{
				smallest_distance = dist;
				closestView = static_cast<Widget*>(view->mChildren[i]);
			}
		}

		view->offsetChildrenPosition(vec2(0.f, view->getCenter().y - closestView->getCenter().y));

	}

	if(event.type == Event::MouseMoved)
	{
		vec2 newPosition(event.mouseMove.x, event.mouseMove.y);

		//Log("Mouse moved");

		if(scrolling)
		{
			//Log("Scrolling!");

			vec2 offset = lastPosition - newPosition;
			offset *= -1.f;
			if(!mScrollsHorizontally)
			{
				offset.x = 0.f;
			}
			if(!mScrollsVertically)
			{
				offset.y = 0.f;
			}
			view->offsetChildrenPosition(offset);

			// apply test offset effect
			/*float biggest_center = view->m_children[0]->getCenter().y;
			float smallest_center = view->m_children[0]->getCenter().y;
			for(std::size_t i = 0; i < view->m_children.size(); ++i)
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
			}*/
		}

		// track mouse
		lastPosition = vec2(event.mouseMove.x, event.mouseMove.y);
	}
}

Widget* UIComponentScroll::getSelectedView(Widget* view)
{
	if(view->mChildren.size() == 0)
		return NULL;

	/*float smallest_distance = fabs(view->m_children[0]->getCenter().y - view->getCenter().y);
	UIView* closestView = view->m_children[0];
	for(std::size_t i = 0; i < view->m_children.size(); ++i)
	{				
		float dist = fabs(view->m_children[i]->getCenter().y - view->getCenter().y);
		if(dist < smallest_distance)
		{
			smallest_distance = dist;
			closestView = view->m_children[i];
		}
	}

	return closestView;*/

	return nullptr;
}


void UIComponentScroll::onUpdate(const Time& time, Widget* view)
{

}

void UIComponentScroll::onRender(GraphicsDevice* renderer, Widget* view)
{
	RectangleShape backRect(view->getRect(), Color::Bittersweet);
	renderer->draw(backRect);
}

NEPHILIM_NS_END