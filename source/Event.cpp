#include <Nephilim/Event.h>

NEPHILIM_NS_BEGIN

/// Returns true if the event refers to a pointer being pressed, like a touch or the mouse button
bool Event::isPointerPressed() const
{
	return (type == MouseButtonPressed || type == TouchPressed);
}
NEPHILIM_NS_END
