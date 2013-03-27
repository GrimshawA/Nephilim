#ifndef PARABOLA_INPUTEVENT_H
#define PARABOLA_INPUTEVENT_H

#include "Platform.h"
#include "Vectors.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API Mouse
{
public :

	////////////////////////////////////////////////////////////
	/// \brief Mouse buttons
	///
	////////////////////////////////////////////////////////////
	enum Button
	{
		Left,       ///< The left mouse button
		Right,      ///< The right mouse button
		Middle,     ///< The middle (wheel) mouse button
		XButton1,   ///< The first extra mouse button
		XButton2,   ///< The second extra mouse button

		ButtonCount ///< Keep last -- the total number of mouse buttons
	};

	////////////////////////////////////////////////////////////
	/// \brief Check if a mouse button is pressed
	///
	/// \param button Button to check
	///
	/// \return True if the button is pressed, false otherwise
	///
	////////////////////////////////////////////////////////////
//	static bool isButtonPressed(Button button);

	////////////////////////////////////////////////////////////
	/// \brief Get the current position of the mouse in desktop coordinates
	///
	/// This function returns the global position of the mouse
	/// cursor on the desktop.
	///
	/// \return Current position of the mouse
	///
	////////////////////////////////////////////////////////////
	//static Vector2i getPosition();

	////////////////////////////////////////////////////////////
	/// \brief Get the current position of the mouse in window coordinates
	///
	/// This function returns the current position of the mouse
	/// cursor, relative to the given window.
	///
	/// \param relativeTo Reference window
	///
	/// \return Current position of the mouse
	///
	////////////////////////////////////////////////////////////
	//static Vector2i getPosition(const Window& relativeTo);

	////////////////////////////////////////////////////////////
	/// \brief Set the current position of the mouse in desktop coordinates
	///
	/// This function sets the global position of the mouse
	/// cursor on the desktop.
	///
	/// \param position New position of the mouse
	///
	////////////////////////////////////////////////////////////
	//static void setPosition(const Vector2i& position);

	////////////////////////////////////////////////////////////
	/// \brief Set the current position of the mouse in window coordinates
	///
	/// This function sets the current position of the mouse
	/// cursor, relative to the given window.
	///
	/// \param position New position of the mouse
	/// \param relativeTo Reference window
	///
	////////////////////////////////////////////////////////////
//	static void setPosition(const Vector2i& position, const Window& relativeTo);
};


class PARABOLA_API Keyboard
{
public :

	////////////////////////////////////////////////////////////
	/// \brief Key codes
	///
	////////////////////////////////////////////////////////////
	enum Key
	{
		A,            ///< The A key
		B,            ///< The B key
		C,            ///< The C key
		D,            ///< The D key
		E,            ///< The E key
		F,            ///< The F key
		G,            ///< The G key
		H,            ///< The H key
		I,            ///< The I key
		J,            ///< The J key
		K,            ///< The K key
		L,            ///< The L key
		M,            ///< The M key
		N,            ///< The N key
		O,            ///< The O key
		P,            ///< The P key
		Q,            ///< The Q key
		R,            ///< The R key
		S,            ///< The S key
		T,            ///< The T key
		U,            ///< The U key
		V,            ///< The V key
		W,            ///< The W key
		X,            ///< The X key
		Y,            ///< The Y key
		Z,            ///< The Z key
		Num0,         ///< The 0 key
		Num1,         ///< The 1 key
		Num2,         ///< The 2 key
		Num3,         ///< The 3 key
		Num4,         ///< The 4 key
		Num5,         ///< The 5 key
		Num6,         ///< The 6 key
		Num7,         ///< The 7 key
		Num8,         ///< The 8 key
		Num9,         ///< The 9 key
		Escape,       ///< The Escape key
		LControl,     ///< The left Control key
		LShift,       ///< The left Shift key
		LAlt,         ///< The left Alt key
		LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
		RControl,     ///< The right Control key
		RShift,       ///< The right Shift key
		RAlt,         ///< The right Alt key
		RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
		Menu,         ///< The Menu key
		LBracket,     ///< The [ key
		RBracket,     ///< The ] key
		SemiColon,    ///< The ; key
		Comma,        ///< The , key
		Period,       ///< The . key
		Quote,        ///< The ' key
		Slash,        ///< The / key
		BackSlash,    ///< The \ key
		Tilde,        ///< The ~ key
		Equal,        ///< The = key
		Dash,         ///< The - key
		Space,        ///< The Space key
		Return,       ///< The Return key
		Back,         ///< The Backspace key
		Tab,          ///< The Tabulation key
		PageUp,       ///< The Page up key
		PageDown,     ///< The Page down key
		End,          ///< The End key
		Home,         ///< The Home key
		Insert,       ///< The Insert key
		Delete,       ///< The Delete key
		Add,          ///< +
		Subtract,     ///< -
		Multiply,     ///< *
		Divide,       ///< /
		Left,         ///< Left arrow
		Right,        ///< Right arrow
		Up,           ///< Up arrow
		Down,         ///< Down arrow
		Numpad0,      ///< The numpad 0 key
		Numpad1,      ///< The numpad 1 key
		Numpad2,      ///< The numpad 2 key
		Numpad3,      ///< The numpad 3 key
		Numpad4,      ///< The numpad 4 key
		Numpad5,      ///< The numpad 5 key
		Numpad6,      ///< The numpad 6 key
		Numpad7,      ///< The numpad 7 key
		Numpad8,      ///< The numpad 8 key
		Numpad9,      ///< The numpad 9 key
		F1,           ///< The F1 key
		F2,           ///< The F2 key
		F3,           ///< The F3 key
		F4,           ///< The F4 key
		F5,           ///< The F5 key
		F6,           ///< The F6 key
		F7,           ///< The F7 key
		F8,           ///< The F8 key
		F9,           ///< The F8 key
		F10,          ///< The F10 key
		F11,          ///< The F11 key
		F12,          ///< The F12 key
		F13,          ///< The F13 key
		F14,          ///< The F14 key
		F15,          ///< The F15 key
		Pause,        ///< The Pause key
		AndroidBack,  ///< Android Back button

		KeyCount      ///< Keep last -- the total number of keyboard keys
	};

	////////////////////////////////////////////////////////////
	/// \brief Check if a key is pressed
	///
	/// \param key Key to check
	///
	/// \return True if the key is pressed, false otherwise
	///
	////////////////////////////////////////////////////////////
	//static bool isKeyPressed(Key key);
};

class PARABOLA_API Joystick
{
public :

	////////////////////////////////////////////////////////////
	/// \brief Constants related to joysticks capabilities
	///
	////////////////////////////////////////////////////////////
	enum
	{
		Count       = 8,  ///< Maximum number of supported joysticks
		ButtonCount = 32, ///< Maximum number of supported buttons
		AxisCount   = 8   ///< Maximum number of supported axes
	};

	////////////////////////////////////////////////////////////
	/// \brief Axes supported by SFML joysticks
	///
	////////////////////////////////////////////////////////////
	enum Axis
	{
		X,    ///< The X axis
		Y,    ///< The Y axis
		Z,    ///< The Z axis
		R,    ///< The R axis
		U,    ///< The U axis
		V,    ///< The V axis
		PovX, ///< The X axis of the point-of-view hat
		PovY  ///< The Y axis of the point-of-view hat
	};

	////////////////////////////////////////////////////////////
	/// \brief Check if a joystick is connected
	///
	/// \param joystick Index of the joystick to check
	///
	/// \return True if the joystick is connected, false otherwise
	///
	////////////////////////////////////////////////////////////
	//static bool isConnected(unsigned int joystick);

	////////////////////////////////////////////////////////////
	/// \brief Return the number of buttons supported by a joystick
	///
	/// If the joystick is not connected, this function returns 0.
	///
	/// \param joystick Index of the joystick
	///
	/// \return Number of buttons supported by the joystick
	///
	////////////////////////////////////////////////////////////
	//static unsigned int getButtonCount(unsigned int joystick);

	////////////////////////////////////////////////////////////
	/// \brief Check if a joystick supports a given axis
	///
	/// If the joystick is not connected, this function returns false.
	///
	/// \param joystick Index of the joystick
	/// \param axis     Axis to check
	///
	/// \return True if the joystick supports the axis, false otherwise
	///
	////////////////////////////////////////////////////////////
	//static bool hasAxis(unsigned int joystick, Axis axis);

	////////////////////////////////////////////////////////////
	/// \brief Check if a joystick button is pressed
	///
	/// If the joystick is not connected, this function returns false.
	///
	/// \param joystick Index of the joystick
	/// \param button   Button to check
	///
	/// \return True if the button is pressed, false otherwise
	///
	////////////////////////////////////////////////////////////
	//static bool isButtonPressed(unsigned int joystick, unsigned int button);

	////////////////////////////////////////////////////////////
	/// \brief Get the current position of a joystick axis
	///
	/// If the joystick is not connected, this function returns 0.
	///
	/// \param joystick Index of the joystick
	/// \param axis     Axis to check
	///
	/// \return Current position of the axis, in range [-100 .. 100]
	///
	////////////////////////////////////////////////////////////
	//static float getAxisPosition(unsigned int joystick, Axis axis);

	////////////////////////////////////////////////////////////
	/// \brief Update the states of all joysticks
	///
	/// This function is used internally by SFML, so you normally
	/// don't have to call it explicitely. However, you may need to
	/// call it if you have no window yet (or no window at all):
	/// in this case the joysticks states are not updated automatically.
	///
	////////////////////////////////////////////////////////////
	//static void update();
};

class PARABOLA_API Event{
public:
	float x,y;

	Keyboard::Key getKeyCode()
	{
		return key.code;
	}

	bool isPointerDown()
	{
		return (type == MouseButtonPressed || type == TouchPressed);
	}

	bool isPointerReleased()
	{
		return (type == MouseButtonReleased || type == TouchReleased);
	}

	bool isPointerMoved()
	{
		return (type == MouseMoved || type == TouchMoved);
	}

	Vec2i getPointerPosition()
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
			return Vec2i((int)x, (int)y);
		}
		else return Vec2i(0,0);
	}

	////////////////////////////////////////////////////////////
	/// \brief Size events parameters (Resized)
	///
	////////////////////////////////////////////////////////////
	struct SizeEvent
	{
		unsigned int width;  ///< New width, in pixels
		unsigned int height; ///< New height, in pixels
	};

	////////////////////////////////////////////////////////////
	/// \brief Keyboard event parameters (KeyPressed, KeyReleased)
	///
	////////////////////////////////////////////////////////////
	struct KeyEvent
	{
		Keyboard::Key code;    ///< Code of the key that has been pressed
		bool          alt;     ///< Is the Alt key pressed?
		bool          control; ///< Is the Control key pressed?
		bool          shift;   ///< Is the Shift key pressed?
		bool          system;  ///< Is the System key pressed?
	};

	////////////////////////////////////////////////////////////
	/// \brief Text event parameters (TextEntered)
	///
	////////////////////////////////////////////////////////////
	struct TextEvent
	{
		Uint32 unicode; ///< UTF-32 unicode value of the character
	};

	////////////////////////////////////////////////////////////
	/// \brief Mouse move event parameters (MouseMoved)
	///
	////////////////////////////////////////////////////////////
	struct MouseMoveEvent
	{
		int x; ///< X position of the mouse pointer, relative to the left of the owner window
		int y; ///< Y position of the mouse pointer, relative to the top of the owner window
	};

	////////////////////////////////////////////////////////////
	/// \brief Mouse buttons events parameters
	///        (MouseButtonPressed, MouseButtonReleased)
	///
	////////////////////////////////////////////////////////////
	struct MouseButtonEvent
	{
		Mouse::Button button; ///< Code of the button that has been pressed
		int           x;      ///< X position of the mouse pointer, relative to the left of the owner window
		int           y;      ///< Y position of the mouse pointer, relative to the top of the owner window
	};

	////////////////////////////////////////////////////////////
	/// \brief Mouse wheel events parameters (MouseWheelMoved)
	///
	////////////////////////////////////////////////////////////
	struct MouseWheelEvent
	{
		int delta; ///< Number of ticks the wheel has moved (positive is up, negative is down)
		int x;     ///< X position of the mouse pointer, relative to the left of the owner window
		int y;     ///< Y position of the mouse pointer, relative to the top of the owner window
	};

	////////////////////////////////////////////////////////////
	/// \brief Joystick connection events parameters
	///        (JoystickConnected, JoystickDisconnected)
	///
	////////////////////////////////////////////////////////////
	struct JoystickConnectEvent
	{
		unsigned int joystickId; ///< Index of the joystick (in range [0 .. Joystick::Count - 1])
	};

	////////////////////////////////////////////////////////////
	/// \brief Joystick axis move event parameters (JoystickMoved)
	///
	////////////////////////////////////////////////////////////
	struct JoystickMoveEvent 
	{
		unsigned int   joystickId; ///< Index of the joystick (in range [0 .. Joystick::Count - 1])
		Joystick::Axis axis;       ///< Axis on which the joystick moved
		float          position;   ///< New position on the axis (in range [-100 .. 100])
	};

	////////////////////////////////////////////////////////////
	/// \brief Joystick buttons events parameters
	///        (JoystickButtonPressed, JoystickButtonReleased)
	///
	////////////////////////////////////////////////////////////
	struct JoystickButtonEvent
	{
		unsigned int joystickId; ///< Index of the joystick (in range [0 .. Joystick::Count - 1])
		unsigned int button;     ///< Index of the button that has been pressed (in range [0 .. Joystick::ButtonCount - 1])
	};

	////////////////////////////////////////////////////////////
	/// \brief Enumeration of the different types of events
	///
	////////////////////////////////////////////////////////////
	enum EventType
	{
		Closed,                 ///< The window requested to be closed
		Resized,                ///< The window was resized
		LostFocus,              ///< The window lost the focus
		GainedFocus,            ///< The window gained the focus
		TextEntered,            ///< A character was entered
		KeyPressed,             ///< A key was pressed
		KeyReleased,            ///< A key was released
		MouseWheelMoved,        ///< The mouse wheel was scrolled
		MouseButtonPressed,     ///< A mouse button was pressed
		MouseButtonReleased,    ///< A mouse button was released
		MouseMoved,             ///< The mouse cursor moved
		MouseEntered,           ///< The mouse cursor entered the area of the window
		MouseLeft,              ///< The mouse cursor left the area of the window
		JoystickButtonPressed,  ///< A joystick button was pressed
		JoystickButtonReleased, ///< A joystick button was released
		JoystickMoved,          ///< The joystick moved along an axis
		JoystickConnected,      ///< A joystick was connected
		JoystickDisconnected,   ///< A joystick was disconnected


		TouchPressed,
		TouchReleased,
		TouchMoved,
		Resume,

		Count                   ///< Keep last -- the total number of event types
	};

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	EventType type; ///< Type of the event

	union
	{
		SizeEvent            size;            ///< Size event parameters
		KeyEvent             key;             ///< Key event parameters
		TextEvent            text;            ///< Text event parameters
		MouseMoveEvent       mouseMove;       ///< Mouse move event parameters
		MouseButtonEvent     mouseButton;     ///< Mouse button event parameters
		MouseWheelEvent      mouseWheel;      ///< Mouse wheel event parameters
		JoystickMoveEvent    joystickMove;    ///< Joystick move event parameters
		JoystickButtonEvent  joystickButton;  ///< Joystick button event parameters
		JoystickConnectEvent joystickConnect; ///< Joystick (dis)connect event parameters
	};


};

PARABOLA_NAMESPACE_END
#endif
