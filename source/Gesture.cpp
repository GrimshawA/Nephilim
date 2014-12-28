#include <Nephilim/Gesture.h>
#include <Nephilim/Event.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Math/Math.h>

NEPHILIM_NS_BEGIN

void PinchGesture::pushEvent(const Event& event)
{
	if(event.type == Event::TouchPressed)
	{
		PointerInfo p;
		p.id = event.touch.id;
		p.x = event.touch.x;
		p.y = event.touch.y;
		pressed_ids.push_back(p);

		if(pressed_ids.size() == 2)
		{
			// calculate initial distance
			initial_distance = math::distance(pressed_ids[0].x, pressed_ids[0].y, pressed_ids[1].x, pressed_ids[1].y);
			last_distance = initial_distance;
		}
	}

	if(event.type == Event::TouchReleased)
	{
		std::vector<PointerInfo>::iterator it = pressed_ids.begin();
		while(it != pressed_ids.end())
		{
			if((*it).id == event.touch.id)
			{
				it = pressed_ids.erase(it);
			}
			else
				++it;
		}
	}

	if(event.type == Event::TouchMoved)
	{
		// update the positions
		for(unsigned int i = 0; i < pressed_ids.size(); ++i)
		{
			if(pressed_ids[i].id == event.touch.id)
			{
				pressed_ids[i].x = event.touch.x;
				pressed_ids[i].y = event.touch.y;
			}
		}

		// Only be responsive with two fingers laid down
		if(pressed_ids.size() == 2)
		{
			float curr_distance = math::distance(pressed_ids[0].x, pressed_ids[0].y, pressed_ids[1].x, pressed_ids[1].y);
			Log("Pinch gesture distance: %f", math::distance(pressed_ids[0].x, pressed_ids[0].y, pressed_ids[1].x, pressed_ids[1].y));
			onPinch(curr_distance / last_distance);

			last_distance = curr_distance;
		}
	}
}

NEPHILIM_NS_END
