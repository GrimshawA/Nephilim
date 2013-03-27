/*#ifndef PARABOLA_EVENTS_H
#define PARABOLA_EVENTS_H

#include "Platform.h"
#include "Strings.h"
#include "Vectors.h"
#include <vector>

#include <SFML/Window/Event.hpp>


PARABOLA_NAMESPACE_BEGIN

	typedef unsigned long Key;
	class Window;
	class Event;
	class EventHandler;

	/**
		\namespace Keyboard
		\brief Holds all supported keys from the keyboard

		Basically a rip-off from SFML 2
	*/
	/*namespace Keyboard{
		enum  	Key { 
			A, 
			B, 
			C, 
			D, 
			E, 
			F, 
			G, 
			H, 
			I, 
			J, 
			K, 
			L, 
			M, 
			N, 
			O, 
			P, 
			Q, 
			R, 
			S, 
			T, 
			U, 
			V, 
			W, 
			X, 
			Y, 
			Z, 
			Num0, 
			Num1, 
			Num2, 
			Num3, 
			Num4, 
			Num5, 
			Num6, 
			Num7, 
			Num8, 
			Num9, 
			Escape, 
			LControl, 
			LShift, 
			LAlt, 
			LSystem, 
			RControl, 
			RShift, 
			RAlt, 
			RSystem, 
			Menu, 
			LBracket, 
			RBracket, 
			SemiColon, 
			Comma, 
			Period, 
			Quote, 
			Slash, 
			BackSlash, 
			Tilde, 
			Equal, 
			Dash, 
			Space, 
			Return, 
			Back, 
			Tab, 
			PageUp, 
			PageDown, 
			End, 
			Home, 
			Insert, 
			Delete, 
			Add, 
			Subtract, 
			Multiply, 
			Divide, 
			Left, 
			Right, 
			Up, 
			Down, 
			Numpad0, 
			Numpad1, 
			Numpad2, 
			Numpad3, 
			Numpad4, 
			Numpad5, 
			Numpad6, 
			Numpad7, 
			Numpad8, 
			Numpad9, 
			F1, 
			F2, 
			F3, 
			F4, 
			F5, 
			F6, 
			F7, 
			F8, 
			F9, 
			F10, 
			F11, 
			F12, 
			F13, 
			F14, 
			F15, 
			Pause, 
			KeyCount 
		};
	};*/

	/**
		\namespace Mouse
		\brief Holds all supported mouse buttons

		Basically a rip-off from SFML 2
	*/
	/*namespace Mouse{
		enum  	Button { 
			Left, 
			Right, 
			Middle, 
			XButton1, 
			XButton2, 
			ButtonCount
		};
	};*/




	/**
		\ingroup Core
		\class EventDispatcher
		\brief Represents an event manager, that always exists in a window

		You profit from registering all your event handlers in the event dispatcher instead of feeding each one
		individually from each event. This is because the time deciding what kind of event it is for the right callback
		is only done once.

		\todo fix key modifiers on handler dispatching
	*/
	/*class PARABOLA_API EventDispatcher{
	public:
		/// Catches one event from the window event queue.
		/// Similar to Window->GetEvent() but if send_to_handlers is true
		/// it sends the event to all handlers
		bool catchEvent(Event &event, bool send_to_handlers = true);

		/// Dispatches the event to the handlers, which will callback the right event
		void dispatch(const Event &event);

		/// Registers a new handler to receive events
		void registerHandler(EventHandler* handler);
		/// Unregisters a handler from event dispatch list
		void unregisterHandler(EventHandler* handler);
		/// Clears all handlers
		void clearHandlers();
		/// Get the count of event handlers
		int handlerCount();
		/// Get the handler at index
		EventHandler* handlerAt(int index);		


		/// Get real time state of a key
		static bool isKeyPressed(Keyboard::Key key);
		/// Get real time state of a mouse button
		static bool isMouseButtonPressed(Mouse::Button button);

		/// Translates a key into libRocket key
		static Key translateToRocketKey(Key key);
		/// Translates a key from libRocket into a normal one
		static Key translateFromRocketKey(Key key);
		/// Translates a string with the key to its code
		static Key translateFromString(String key_name);

	private:
		friend class Window; // Only Window accesses private members
		EventDispatcher(); // Constructor is private. Friends only

		std::vector<EventHandler*> myHandlers; // For dispatching events
		Window *Parent;
	};*/

	/**
		\ingroup Core
		\class Event
		\brief Represents one event of a window

		You can feed your event handlers manually from an event, but that may be not desirable when you own more than one. 
		Check the EventDispatcher documentation.
	*/
	/*class PARABOLA_API Event : public sf::Event{
	public:
		/// Creates an empty event to be filled later
		Event();

		/// Get the current position of the mouse, globally
		static Vec2i getGlobalMousePosition();

		/// Get the current position of the mouse based on the engine window
		static Vec2i getLocalMousePosition();

		/// Dispatches the event to the handler, which will have a callback for the specific kind of event
		void dispatch(EventHandler *handler);

		/// Get the x position of the mouse in a mouse move or mouse press/release event
		int mouseX();
		/// Get the y position of the mouse in a mouse move or mouse press/release event
		int mouseY();
		/// Get the key code for the current event
		int getKeyCode();
		/// Get the mouse button code for the current event
		int mouse();

		/// Get the joystick id
		int getJoystickId();

		/// Get the joystick move position
		float getJoystickMovePosition();

		/// Get the joystick axis
		int getJoystickAxis();

		/// Get the wheel delta
		int getWheelDelta();

		enum EventType{
			Closed,                 
			Resized,                
			LostFocus,              
			GainedFocus,            
			TextEntered,            
			KeyPressed,             
			KeyReleased,            
			MouseWheelMoved,        
			MouseButtonPressed,     
			MouseButtonReleased,    
			MouseMoved,             
			MouseEntered,           
			MouseLeft,              
			JoystickButtonPressed,  
			JoystickButtonReleased, 
			JoystickMoved,          
			JoystickConnected,      
			JoystickDisconnected,
			Click, /// Only for events filtered by rocket
			DoubleClick, /// Only for events filtered by rocket
			Count  
		};

		
	};

PARABOLA_NAMESPACE_END
#endif*/