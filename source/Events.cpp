#ifndef MINIMAL_BUILD

#include "Nephilim/Events.h"
#include "Nephilim/Window.h"
#include "Nephilim/EventHandler.h"
#include "Nephilim/Engine.h"
#include <Rocket/Core/Input.h>

NEPHILIM_NS_BEGIN

/// Catches one event from the window event queue.
/// Similar to Window->GetEvent() but if send_to_handlers is true
/// it sends the event to all handlers
bool EventDispatcher::catchEvent(Event &event, bool send_to_handlers){
	bool r = Parent->pollEvent(event);

	if(r && send_to_handlers){
		//dispatch
		dispatch(event);
	}

	return r;
};




/// Dispatches the event to the handlers, which will callback the right event
void EventDispatcher::dispatch(const Event &event){
	if(myHandlers.size() == 0)return;

	switch(event.type){
			case Event::MouseButtonPressed:
				for(unsigned int i = 0; i < myHandlers.size(); i++){
					myHandlers[i]->OnMouseButtonDown(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y, 0);
				}break;
			case Event::MouseButtonReleased:
				for(unsigned int i = 0; i < myHandlers.size(); i++){
					myHandlers[i]->OnMouseButtonUp(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y, 0);				
				}break;
			case Event::MouseMoved:				
				for(unsigned int i = 0; i < myHandlers.size(); i++){
					myHandlers[i]->OnMouseMove(event.mouseMove.x, event.mouseMove.y, 0);
				}break;
			case Event::MouseWheelMoved:
				for(unsigned int i = 0; i < myHandlers.size(); i++){
					myHandlers[i]->OnMouseWheel(event.mouseWheel.delta, 0);
				}break;
			case Event::KeyPressed:
				for(unsigned int i = 0; i < myHandlers.size(); i++){
					myHandlers[i]->OnKeyPress(event.key.code, 0);				
				}break;
			case Event::KeyReleased:
				for(unsigned int i = 0; i < myHandlers.size(); i++){
					myHandlers[i]->OnKeyReleased(event.key.code, 0);
				}break;
			case Event::TextEntered:
				for(unsigned int i = 0; i < myHandlers.size(); i++){
					myHandlers[i]->OnTextEntered(event.text.unicode);
				}break;
	}
};

/// Registers a new handler to receive events
void EventDispatcher::registerHandler(EventHandler* handler){
	myHandlers.push_back(handler);
};
/// Unregisters a handler from event dispatch list
void EventDispatcher::unregisterHandler(EventHandler* handler){
	myHandlers.erase(find(myHandlers.begin(), myHandlers.end(),handler));
};
/// Clears all handlers
void EventDispatcher::clearHandlers(){
	myHandlers.clear();
};

/// Get the count of event handlers
int EventDispatcher::handlerCount(){
	return (int)myHandlers.size();
};
/// Get the handler at index
EventHandler* EventDispatcher::handlerAt(int index){
	if(index < 0 || (unsigned int)index <= myHandlers.size())return NULL;
	else{
		return myHandlers[index];
	}
};	


/// Get real time state of a key
bool EventDispatcher::isKeyPressed(Keyboard::Key key){
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
};

/// Get real time state of a mouse button
bool EventDispatcher::isMouseButtonPressed(Mouse::Button button){
	return sf::Mouse::isButtonPressed((sf::Mouse::Button)button);
};


/// Translates a key from libRocket into a normal one
Key EventDispatcher::translateFromRocketKey(Key key){
	switch(key){
			case Rocket::Core::Input::KI_DOWN: return Keyboard::Down;
			case Rocket::Core::Input::KI_UP: return Keyboard::Up;
			case Rocket::Core::Input::KI_LEFT: return Keyboard::Left;
			case Rocket::Core::Input::KI_RIGHT: return Keyboard::Right;

			case Rocket::Core::Input::KI_A: return Keyboard::A;
			case Rocket::Core::Input::KI_B: return Keyboard::B;
			case Rocket::Core::Input::KI_C: return Keyboard::C;
			case Rocket::Core::Input::KI_D: return Keyboard::D;
			case Rocket::Core::Input::KI_E: return Keyboard::E;
			case Rocket::Core::Input::KI_F: return Keyboard::F;
			case Rocket::Core::Input::KI_G: return Keyboard::G;
			case Rocket::Core::Input::KI_H: return Keyboard::H;
			case Rocket::Core::Input::KI_I: return Keyboard::I;
			case Rocket::Core::Input::KI_J: return Keyboard::J;
			case Rocket::Core::Input::KI_K: return Keyboard::K;
			case Rocket::Core::Input::KI_L: return Keyboard::L;
			case Rocket::Core::Input::KI_M: return Keyboard::M;
			case Rocket::Core::Input::KI_N: return Keyboard::N;
			case Rocket::Core::Input::KI_O: return Keyboard::O;
			case Rocket::Core::Input::KI_P: return Keyboard::P;
			case Rocket::Core::Input::KI_Q: return Keyboard::Q;
			case Rocket::Core::Input::KI_R: return Keyboard::R;
			case Rocket::Core::Input::KI_S: return Keyboard::S;
			case Rocket::Core::Input::KI_T: return Keyboard::T;
			case Rocket::Core::Input::KI_U: return Keyboard::U;
			case Rocket::Core::Input::KI_V: return Keyboard::V;
			case Rocket::Core::Input::KI_W: return Keyboard::W;
			case Rocket::Core::Input::KI_X: return Keyboard::X;
			case Rocket::Core::Input::KI_Y: return Keyboard::Y;
			case Rocket::Core::Input::KI_Z: return Keyboard::Z;

			case Rocket::Core::Input::KI_0: return Keyboard::Num0;
			case Rocket::Core::Input::KI_1: return Keyboard::Num1;
			case Rocket::Core::Input::KI_2: return Keyboard::Num2;
			case Rocket::Core::Input::KI_3: return Keyboard::Num3;
			case Rocket::Core::Input::KI_4: return Keyboard::Num4;
			case Rocket::Core::Input::KI_5: return Keyboard::Num5;
			case Rocket::Core::Input::KI_6: return Keyboard::Num6;
			case Rocket::Core::Input::KI_7: return Keyboard::Num7;
			case Rocket::Core::Input::KI_8: return Keyboard::Num8;
			case Rocket::Core::Input::KI_9: return Keyboard::Num9;

			case Rocket::Core::Input::KI_NUMPAD0: return Keyboard::Numpad0;
			case Rocket::Core::Input::KI_NUMPAD1: return Keyboard::Numpad1;
			case Rocket::Core::Input::KI_NUMPAD2: return Keyboard::Numpad2;
			case Rocket::Core::Input::KI_NUMPAD3: return Keyboard::Numpad3;
			case Rocket::Core::Input::KI_NUMPAD4: return Keyboard::Numpad4;
			case Rocket::Core::Input::KI_NUMPAD5: return Keyboard::Numpad5;
			case Rocket::Core::Input::KI_NUMPAD6: return Keyboard::Numpad6;
			case Rocket::Core::Input::KI_NUMPAD7: return Keyboard::Numpad7;
			case Rocket::Core::Input::KI_NUMPAD8: return Keyboard::Numpad8;
			case Rocket::Core::Input::KI_NUMPAD9: return Keyboard::Numpad9;

			case Rocket::Core::Input::KI_F1: return Keyboard::F1;
			case Rocket::Core::Input::KI_F2: return Keyboard::F2;
			case Rocket::Core::Input::KI_F3: return Keyboard::F3;
			case Rocket::Core::Input::KI_F4: return Keyboard::F4;
			case Rocket::Core::Input::KI_F5: return Keyboard::F5;
			case Rocket::Core::Input::KI_F6: return Keyboard::F6;
			case Rocket::Core::Input::KI_F7: return Keyboard::F7;
			case Rocket::Core::Input::KI_F8: return Keyboard::F8;
			case Rocket::Core::Input::KI_F9: return Keyboard::F9;
			case Rocket::Core::Input::KI_F10: return Keyboard::F10;
			case Rocket::Core::Input::KI_F11: return Keyboard::F11;
			case Rocket::Core::Input::KI_F12: return Keyboard::F12;
			case Rocket::Core::Input::KI_F13: return Keyboard::F13;
			case Rocket::Core::Input::KI_F14: return Keyboard::F14;
			case Rocket::Core::Input::KI_F15: return Keyboard::F15;

			case Rocket::Core::Input::KI_HOME: return Keyboard::Home;
			case Rocket::Core::Input::KI_ESCAPE: return Keyboard::Escape;
			case Rocket::Core::Input::KI_LWIN: return Keyboard::LSystem;
			case Rocket::Core::Input::KI_RWIN: return Keyboard::RSystem;
			case Rocket::Core::Input::KI_RETURN : return Keyboard::Return;


			case Rocket::Core::Input::KI_ADD: return Keyboard::Add;
			case Rocket::Core::Input::KI_BACK: return Keyboard::Back;
			case Rocket::Core::Input::KI_OEM_COMMA: return Keyboard::Comma;
			case Rocket::Core::Input::KI_LSHIFT : return Keyboard::LShift;
			case Rocket::Core::Input::KI_RSHIFT: return Keyboard::RShift;
			case Rocket::Core::Input::KI_RCONTROL : return Keyboard::RControl;
			case Rocket::Core::Input::KI_LCONTROL : return Keyboard::LControl;
			case Rocket::Core::Input::KI_DELETE : return Keyboard::Delete;	
	}

	return 0;
};

/// Translates a string with the key to its code
Key EventDispatcher::translateFromString(String key_name){
	if(key_name.empty())return 0;

	key_name.toLowerCase();

	if(key_name[0] == 'a')return Keyboard::A;
	if(key_name[0] == 'b')return Keyboard::B;
	if(key_name[0] == 'c')return Keyboard::C;
	if(key_name[0] == 'd')return Keyboard::D;
	if(key_name[0] == 'e')return Keyboard::E;
	if(key_name[0] == 'f')return Keyboard::F;
	if(key_name[0] == 'g')return Keyboard::G;
	if(key_name[0] == 'h')return Keyboard::H;
	if(key_name[0] == 'i')return Keyboard::I;
	if(key_name[0] == 'j')return Keyboard::J;
	if(key_name[0] == 'k')return Keyboard::K;
	if(key_name[0] == 'l')return Keyboard::L;
	if(key_name[0] == 'm')return Keyboard::M;
	if(key_name[0] == 'n')return Keyboard::N;
	if(key_name[0] == 'o')return Keyboard::O;
	if(key_name[0] == 'p')return Keyboard::P;
	if(key_name[0] == 'q')return Keyboard::Q;
	if(key_name[0] == 'r')return Keyboard::R;
	if(key_name[0] == 's')return Keyboard::S;
	if(key_name[0] == 't')return Keyboard::T;
	if(key_name[0] == 'u')return Keyboard::U;
	if(key_name[0] == 'v')return Keyboard::V;
	if(key_name[0] == 'w')return Keyboard::W;
	if(key_name[0] == 'x')return Keyboard::X;
	if(key_name[0] == 'y')return Keyboard::Y;
	if(key_name[0] == 'z')return Keyboard::Z;

	return 0;
};

EventDispatcher::EventDispatcher(){
	Parent = NULL;
};



/************************************************************************/
/* Event class                                                          */
/************************************************************************/

Event::Event() : sf::Event(){

}

/// Get the x position of the mouse in a mouse move or mouse press/release event
int Event::mouseX(){
	if(type == MouseMoved)
		return (int)mouseMove.x;
	else
		return (int)mouseButton.x;
}
/// Get the y position of the mouse in a mouse move or mouse press/release event
int Event::mouseY(){
	if(type == MouseMoved)
		return (int)mouseMove.y;
	else
		return (int)mouseButton.y;
}

/// Get the key code for the current event
int Event::getKeyCode(){
	return (int)key.code;
};

int Event::mouse(){
	return (int)mouseButton.button;
};

/// Get the wheel delta
int Event::getWheelDelta(){
	return mouseWheel.delta;
};

/// Get the joystick id
int Event::getJoystickId(){
	if(type == Event::JoystickConnected || type == Event::JoystickDisconnected){
		return joystickConnect.joystickId;
	}	
	else if(type == Event::JoystickMoved){
		return joystickMove.joystickId;
	}
	else if(type == Event::JoystickButtonPressed || type == Event::JoystickButtonReleased){
		return joystickButton.joystickId;
	}
	else return -1;
};

/// Get the current position of the mouse, globally
Vec2i Event::getGlobalMousePosition(){
	return Vec2i(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
};

/// Get the current position of the mouse based on the engine window
Vec2i Event::getLocalMousePosition(){
	return Vec2i(sf::Mouse::getPosition(*Engine::instance()->getWindow()).x,sf::Mouse::getPosition(*Engine::instance()->getWindow()).y);
};

/// Get the joystick move position
float Event::getJoystickMovePosition(){
	return joystickMove.position;
}

/// Get the joystick axis
int Event::getJoystickAxis(){
	return joystickMove.axis;
};


void Event::dispatch(EventHandler *handler){
	switch(type){
			case Event::MouseButtonPressed:				
				handler->OnMouseButtonDown(mouseButton.button, mouseButton.x, mouseButton.y, 0);				
				break;
			case Event::MouseButtonReleased:
				handler->OnMouseButtonUp(mouseButton.button, mouseButton.x, mouseButton.y, 0);				
				break;
			case Event::MouseMoved:				
				handler->OnMouseMove(mouseMove.x, mouseMove.y, 0);
				break;
			case Event::MouseWheelMoved:
				handler->OnMouseWheel(mouseWheel.delta, 0);
				break;
			case Event::KeyPressed:
				handler->OnKeyPress(key.code, 0);				
				break;
			case Event::KeyReleased:
				handler->OnKeyReleased(key.code, 0);
				break;
			case Event::TextEntered:
				handler->OnTextEntered(text.unicode);
				break;
	}
};

NEPHILIM_NS_END

#endif