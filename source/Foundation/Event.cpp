#include <Nephilim/Foundation/Event.h>

NEPHILIM_NS_BEGIN

/// Returns true if the event refers to a pointer being pressed, like a touch or the mouse button
bool Event::isPointerPressed() const
{
	return (type == MouseButtonPressed || type == TouchPressed);
}

bool Event::isPointerType() const
{
	return (type == MouseButtonPressed || type == TouchPressed || type == MouseButtonReleased || type == TouchReleased || type == MouseMoved || type == TouchMoved); 
}

vec2i Event::getPointerPosition() const
{
	if(type == MouseButtonPressed)
	{
		return Vec2i(mouseButton.x, mouseButton.y);
	}
	else if(type == MouseButtonReleased)
	{
		return Vec2i(mouseButton.x, mouseButton.y);
	}
	else if(type == MouseMoved)
	{
		return Vec2i(mouseMove.x, mouseMove.y);
	}
	else if(type == TouchPressed || type == TouchReleased || type == TouchMoved)
	{
		return Vec2i((int)touch.x, (int)touch.y);
	}
	else return Vec2i(0,0);
}

void Event::setPointerPosition(vec2i pos)
{
	if(type == MouseButtonPressed || type == MouseButtonReleased)
	{
		mouseButton.x = pos.x;
		mouseButton.y = pos.y;
	}
	else if(type == MouseMoved)
	{
		mouseMove.x = pos.x;
		mouseMove.y = pos.y;
	}
	else if(type == TouchPressed || type == TouchReleased || type == TouchMoved)
	{
		touch.x = pos.x;
		touch.y = pos.y;
	}
}


/// Check if the Event object is a key press with a given key, usually for shorter hand notation 
bool isKeyPress(const Event& event, Keyboard::Key k)
{
	return (event.type == Event::KeyPressed && event.key.code == k);
}

/// Check if the Event object is a key press with a given key, usually for shorter hand notation 
bool isKeyRelease(const Event& event, Keyboard::Key k)
{
	return (event.type == Event::KeyReleased && event.key.code == k);
}

/// Check if the event is a left mouse press
bool isLeftMousePress(const Event& event)
{
	return (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left);
}

/// Check if the event is a left mouse press
bool isRightMousePress(const Event& event)
{
	return (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right);
}

NEPHILIM_NS_END