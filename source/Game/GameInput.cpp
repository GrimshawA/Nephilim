#include <Nephilim/Game/GameInput.h>

NEPHILIM_NS_BEGIN

/// Construct to default values
GameInput::GameInput()
{

}

bool GameInput::getKey(Keyboard::Key key)
{
	if (m_keys.find(key) == m_keys.end())
	{
		m_keys[key] = false;
	}
	return m_keys[key];
}

bool GameInput::getJoystickButton(unsigned int button)
{
	if (m_joystickKeys.find(button) == m_joystickKeys.end())
	{
		m_joystickKeys[button] = false;
	}
	return m_joystickKeys[button];
}

bool GameInput::getMouseButton(Mouse::Button button)
{
	if (m_mouseButtons.find(button) == m_mouseButtons.end())
	{
		m_mouseButtons[button] = false;
	}
	return m_mouseButtons[button];
}

Vec2i GameInput::getMousePosition()
{
	return m_mousePosition;
}

void GameInput::update(const Event& event)
{
	switch (event.type)
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

NEPHILIM_NS_END