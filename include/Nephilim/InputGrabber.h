#ifndef NephilimInputGrabber_h__
#define NephilimInputGrabber_h__

#include "Platform.h"
#include "Event.h"

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN

/**
	\ingroup Core
	\class InputGrabber
	\brief Proxy to catch and handle events easily
*/
class NEPHILIM_API InputGrabber
{
public:
	InputGrabber()
	{

	}

	void update(const Event& event)
	{
		switch(event.type)
		{
			case Event::KeyPressed:
			{
				m_keys[event.key.code] = true;
			}break;

			case Event::KeyReleased:
			{
				m_keys[event.key.code] = false;
			}break;

			case Event::MouseButtonPressed:
			{
				m_mouseButtons[event.mouseButton.button] = true;
				m_mousePosition = Vec2i(event.mouseButton.x, event.mouseButton.y);
			}break;

			case Event::MouseButtonReleased:
			{
				m_mouseButtons[event.mouseButton.button] = false;
				m_mousePosition = Vec2i(event.mouseButton.x, event.mouseButton.y);
			}break;
			case Event::MouseMoved:
			{
				m_mousePosition = Vec2i(event.mouseMove.x, event.mouseMove.y);
			}break;
		}
	}

	bool getKey(Keyboard::Key key)
	{
		if(m_keys.find(key) == m_keys.end())
		{
			m_keys[key] = false;
		}
		return m_keys[key];
	}
	bool getMouseButton(Mouse::Button button)
	{
		if(m_mouseButtons.find(button) == m_mouseButtons.end())
		{
			m_mouseButtons[button] = false;
		}
		return m_mouseButtons[button];
	}

	Vec2i getMousePosition()
	{
		return m_mousePosition;
	}

	std::map<Keyboard::Key, bool> m_keys;
	std::map<Mouse::Button, bool> m_mouseButtons;

	Vec2i m_mousePosition;
};

NEPHILIM_NS_END
#endif // NephilimInputGrabber_h__
