#include <Nephilim/Game/GameInput.h>

#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/ConfigFile.h>

NEPHILIM_NS_BEGIN

GameInput* gInput = nullptr;

/// Construct to default values
GameInput::GameInput()
{
	gInput = this;
}

void GameInput::loadKeyBindings(const String& filename)
{
	ConfigFile file;
	file.loadFromFile(filename);

	ConfigFile::ObjectData* p1 = file.getObject("P1_Joystick");
	if (p1)
	{
		for (std::size_t i = 0; i < p1->members.size(); ++i)
		{
			Log("Action Binding: %s = %s", p1->members[i].c_str(), p1->values[i].c_str());

			GameInputMapping mapping;
			mapping.b = p1->values[i].toInt();
			mapping.name = p1->members[i];
			mappings[p1->members[i]] = mapping;
		}
	}
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

void GameInput::update(const Time& deltaTime)
{
	for (auto& mapping : mappings)
	{
		if (getJoystickButton(mapping.second.b))
		{
			testEmit(mapping.first);
		}
	}
}

Vec2i GameInput::getMousePosition()
{
	return m_mousePosition;
}

void GameInput::updateWithEvent(const Event& event)
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

	case Event::JoystickMoved:
	{
		m_joystickAxisState[event.joystickMove.joystickId][event.joystickMove.axis] = event.joystickMove.position;
	}
	break;

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

/// Check the current value of a joystick axis
float GameInput::getJoystickAxis(int joystick, int axis)
{
	return m_joystickAxisState[joystick][axis]; 
}

NEPHILIM_NS_END