#ifndef PARABOLA_EVENTHANDLER_H
#define PARABOLA_EVENTHANDLER_H

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN

	/**
		\ingroup Core
		\class EventHandler
		\brief Base class for event handlers.

		In practice, you may use this class when you want to feed events to an object.

		If you implement these methods, you can then simply do Event.feedEventHandler(myObject);

		\todo example
	*/
	class PARABOLA_API EventHandler{
	public:
		/// Called when a mouse button is pressed down
		/// x and y are the click position
		/// keyMod contains the currently pressed modifier keys like CTRL, SHIFT etc.
		virtual void OnMouseButtonDown(unsigned int MouseButton, int x, int y, int keyMod);
		/// Called when a mouse button is released
		/// x and y are the button release position
		/// keyMod contains the currently pressed modifier keys like CTRL, SHIFT etc.
		virtual void OnMouseButtonUp(unsigned int MouseButton, int x, int y, int keyMod);
		/// Called when a mouse is moved
		/// x and y represent the new position of the mouse cursor
		/// keyMod contains the currently pressed modifier keys like CTRL, SHIFT etc.
		virtual void OnMouseMove(int x, int y, int keyMod);
		/// Called when the mouse wheel is rotated
		/// delta represents the amount of movement done in the wheel
		/// keyMod contains the currently pressed modifier keys like CTRL, SHIFT etc.
		virtual void OnMouseWheel(int delta, int keyMod);
		/// Called a key is held down
		/// Key represents the key being pressed
		/// keyMod contains the currently pressed modifier keys like CTRL, SHIFT etc.
		virtual void OnKeyPress(unsigned int Key, int keyMod);
		/// Called when text is entered
		/// Key represents the character pressed, normally in the ASCII range
		virtual void OnTextEntered(unsigned int Key);
		/// Called when a key is released
		/// Key represents the key being released
		/// keyMod contains the currently pressed modifier keys like CTRL, SHIFT etc.
		virtual void OnKeyReleased(unsigned int Key, int keyMod);
	};

PARABOLA_NAMESPACE_END
#endif