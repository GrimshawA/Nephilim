#ifndef NephilimGameInput_h__
#define NephilimGameInput_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Time.h>
#include <Nephilim/Foundation/Event.h>

#include <sigc++/sigc++.h>
#include <vector>
#include <map>

NEPHILIM_NS_BEGIN

/**
	\class GameInputMapping
	\brief Maps an action name to a input state
*/
class NEPHILIM_API GameInputMapping
{
public:

	String name;
	int    b;
};

/**
	\class GameInput
	\brief Class to query input state etc
*/
class NEPHILIM_API GameInput
{
public:

	sigc::signal<void, String> testEmit;

	/// Game-wide list of keys and their assignments
	std::map<String, GameInputMapping> mappings;

	/// Keyboard state
	std::map<Keyboard::Key, bool> m_keys;

	/// Joystick state
	std::map<unsigned int, bool> m_joystickKeys;

	/// Mouse state
	std::map<Mouse::Button, bool> m_mouseButtons;
	Vec2i m_mousePosition;

	/// Joystick axis state, first int is joystick id, for each joystick we have a map of axis id to axis value
	std::map<int, std::map<int, float> > m_joystickAxisState;

public:
	/// Construct to default values
	GameInput();

	void loadKeyBindings(const String& filename);

	/// Update the state of the structure
	void updateWithEvent(const Event& event);

	void update(const Time& deltaTime);

	/// Check if a key is pressed
	bool getKey(Keyboard::Key key);

	/// Check if a given joystick button is being pressed
	bool getJoystickButton(unsigned int button);

	/// Check the current value of a joystick axis
	float getJoystickAxis(int joystick, int axis);

	/// Check if a mouse button is being pressed
	bool getMouseButton(Mouse::Button button);

	/// Get current mouse position
	Vec2i getMousePosition();	
};

/// Global accessors to the input utilities
extern GameInput* gInput;

NEPHILIM_NS_END
#endif // NephilimGameInput_h__
