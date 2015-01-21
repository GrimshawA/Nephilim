#ifndef NephilimGameInput_h__
#define NephilimGameInput_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Event.h>

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN

/**
	\class GameInput
	\brief Class to query input state etc
*/
class NEPHILIM_API GameInput
{
public:

	/// Keyboard state
	std::map<Keyboard::Key, bool> m_keys;

	/// Joystick state
	std::map<unsigned int, bool> m_joystickKeys;

	/// Mouse state
	std::map<Mouse::Button, bool> m_mouseButtons;
	Vec2i m_mousePosition;

public:
	/// Construct to default values
	GameInput();

	/// Update the state of the structure
	void update(const Event& event);

	/// Check if a key is pressed
	bool getKey(Keyboard::Key key);

	/// Check if a given joystick button is being pressed
	bool getJoystickButton(unsigned int button);

	/// Check if a mouse button is being pressed
	bool getMouseButton(Mouse::Button button);

	/// Get current mouse position
	Vec2i getMousePosition();	
};

NEPHILIM_NS_END
#endif // NephilimGameInput_h__
