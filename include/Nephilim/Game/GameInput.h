#ifndef NephilimGameInput_h__
#define NephilimGameInput_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Event.h>

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN

/**
	\ingroup Core
	\class InputGrabber
	\brief Proxy to catch and handle events easily
*/
class NEPHILIM_API GameInput
{
public:
	GameInput()
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

			case Event::JoystickButtonPressed:
			{
				m_joystickKeys[event.joystickButton.button] = true;
			}break;

			case Event::JoystickButtonReleased:
			{
				m_joystickKeys[event.joystickButton.button] = false;

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

	bool getJoystickButton(unsigned int button)
	{
		if (m_joystickKeys.find(button) == m_joystickKeys.end())
		{
			m_joystickKeys[button] = false;
		}
		return m_joystickKeys[button];
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
	std::map<unsigned int, bool> m_joystickKeys;
	std::map<Mouse::Button, bool> m_mouseButtons;

	Vec2i m_mousePosition;
};

NEPHILIM_NS_END
#endif // NephilimGameInput_h__
