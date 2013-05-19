#include "Nephilim/ASEngine.h"
#include "Nephilim/Event.h"

#include "AS/aswrappedcall.h"

#include <stdio.h>

NEPHILIM_NS_BEGIN

/// Exports events as a reference type
bool ASEngine::exportEvents(){
	// Event type
	/*asEngine->RegisterObjectType("Event", sizeof(InputEvent), asOBJ_REF);


	r = asEngine->RegisterObjectBehaviour("Event", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummy2), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("Event", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummy2), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	*/
	exportReferenceDataType("Event");

	int r;
	// Type property
	asEngine->RegisterObjectProperty("Event", "int type", asOFFSET(Event, type));
	asEngine->RegisterObjectProperty("Event", "float x", asOFFSET(Event, touch.x));
	asEngine->RegisterObjectProperty("Event", "float y", asOFFSET(Event, touch.y));

	if(getPortableMode())
	{
		//r = asEngine->RegisterObjectMethod("Event", "int mouseX()", WRAP_MFN(Event, mouseX), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("Event", "int mouseY()", WRAP_MFN(Event, mouseY), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("Event", "int key()", WRAP_MFN(Event, getKeyCode), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("Event", "bool isPointerPressed()", WRAP_MFN(Event, isPointerDown), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("Event", "bool isPointerReleased()", WRAP_MFN(Event, isPointerReleased), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("Event", "bool isPointerMoved()", WRAP_MFN(Event, isPointerMoved), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("Event", "Vec2i getPointerPosition()", WRAP_MFN(Event, getPointerPosition), asCALL_GENERIC); if(r < 0)printf("r %d", r);

		//r = asEngine->RegisterObjectMethod("Event", "int mouse()", WRAP_MFN(Event, mouse), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("Event", "int delta()", WRAP_MFN(Event, getWheelDelta), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("Event", "int getJoystickAxis()", WRAP_MFN(Event, getJoystickAxis), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("Event", "int getJoystickId()", WRAP_MFN(Event, getJoystickId), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("Event", "float getJoystickMovePosition()", WRAP_MFN(Event, getJoystickMovePosition), asCALL_GENERIC); if(r < 0)printf("r %d", r);

		//r = asEngine->RegisterGlobalFunction("Vec2i getGlobalMousePosition()", asFUNCTION(Event::getGlobalMousePosition), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterGlobalFunction("Vec2i getMousePosition()", asFUNCTION(Event::getLocalMousePosition), asCALL_GENERIC); if(r < 0)printf("r %d", r);

	}
	else
	{
		//r = asEngine->RegisterObjectMethod("Event", "int mouseX()", asMETHOD(Event, mouseX), asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("Event", "int mouseY()", asMETHOD(Event, mouseY), asCALL_THISCALL); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("Event", "int key()", asMETHOD(Event, getKeyCode), asCALL_THISCALL); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("Event", "bool isPointerPressed()", asMETHOD(Event, isPointerDown), asCALL_THISCALL); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("Event", "bool isPointerReleased()", asMETHOD(Event, isPointerReleased), asCALL_THISCALL); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("Event", "bool isPointerMoved()", asMETHOD(Event, isPointerMoved), asCALL_THISCALL); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectMethod("Event", "Vec2i getPointerPosition()", asMETHOD(Event, getPointerPosition), asCALL_THISCALL); if(r < 0)printf("r %d", r);

	//	r = asEngine->RegisterObjectMethod("Event", "int mouse()", asMETHOD(Event, mouse), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	//	r = asEngine->RegisterObjectMethod("Event", "int delta()", asMETHOD(Event, getWheelDelta), asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("Event", "int getJoystickAxis()", asMETHOD(Event, getJoystickAxis), asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("Event", "int getJoystickId()", asMETHOD(Event, getJoystickId), asCALL_THISCALL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterObjectMethod("Event", "float getJoystickMovePosition()", asMETHOD(Event, getJoystickMovePosition), asCALL_THISCALL); if(r < 0)printf("r %d", r);

		//r = asEngine->RegisterGlobalFunction("Vec2i getGlobalMousePosition()", asFUNCTION(Event::getGlobalMousePosition), asCALL_CDECL); if(r < 0)printf("r %d", r);
		//r = asEngine->RegisterGlobalFunction("Vec2i getMousePosition()", asFUNCTION(Event::getLocalMousePosition), asCALL_CDECL); if(r < 0)printf("r %d", r);

	}


	// Accessors
	asEngine->RegisterEnum("Events");
	asEngine->RegisterEnumValue("Events", "KeyPressed", Event::KeyPressed);
	asEngine->RegisterEnumValue("Events", "KeyReleased", Event::KeyReleased);
	asEngine->RegisterEnumValue("Events", "TextEntered", Event::TextEntered);

	asEngine->RegisterEnumValue("Events", "Resized", Event::Resized);
	asEngine->RegisterEnumValue("Events", "GainedFocus", Event::GainedFocus);
	asEngine->RegisterEnumValue("Events", "LostFocus", Event::LostFocus);
	asEngine->RegisterEnumValue("Events", "Closed", Event::Closed);


	asEngine->RegisterEnumValue("Events", "MouseButtonPressed", Event::MouseButtonPressed);
	asEngine->RegisterEnumValue("Events", "MouseButtonReleased", Event::MouseButtonReleased);
	asEngine->RegisterEnumValue("Events", "MouseMoved", Event::MouseMoved);
	asEngine->RegisterEnumValue("Events", "MouseWheelMoved", Event::MouseWheelMoved);
	asEngine->RegisterEnumValue("Events", "MouseEntered", Event::MouseEntered);
	asEngine->RegisterEnumValue("Events", "MouseLeft", Event::MouseLeft);


	asEngine->RegisterEnumValue("Events", "JoystickButtonPressed", Event::JoystickButtonPressed);
	asEngine->RegisterEnumValue("Events", "JoystickButtonReleased", Event::JoystickButtonReleased);
	asEngine->RegisterEnumValue("Events", "JoystickConnected", Event::JoystickConnected);
	asEngine->RegisterEnumValue("Events", "JoystickDisconnected", Event::JoystickDisconnected);
	asEngine->RegisterEnumValue("Events", "JoystickMoved", Event::JoystickMoved);

	asEngine->RegisterEnumValue("Events", "TouchPressed", Event::TouchPressed);
	asEngine->RegisterEnumValue("Events", "TouchReleased", Event::TouchReleased);
	asEngine->RegisterEnumValue("Events", "TouchMoved", Event::TouchMoved);


/*	asEngine->RegisterEnum("JoystickAxis");
	asEngine->RegisterEnumValue("JoystickAxis", "X", sf::Joystick::X);
	asEngine->RegisterEnumValue("JoystickAxis", "Y", sf::Joystick::Y);
	asEngine->RegisterEnumValue("JoystickAxis", "Z", sf::Joystick::Z);
	asEngine->RegisterEnumValue("JoystickAxis", "R", sf::Joystick::R);
	asEngine->RegisterEnumValue("JoystickAxis", "U", sf::Joystick::U);
	asEngine->RegisterEnumValue("JoystickAxis", "V", sf::Joystick::V);
	asEngine->RegisterEnumValue("JoystickAxis", "PX", sf::Joystick::PovX);
	asEngine->RegisterEnumValue("JoystickAxis", "PY", sf::Joystick::PovY);*/

	asEngine->RegisterEnum("Keyboard");
	asEngine->RegisterEnumValue("Keyboard", "A", Keyboard::A);
	asEngine->RegisterEnumValue("Keyboard", "B", Keyboard::B);
	asEngine->RegisterEnumValue("Keyboard", "C", Keyboard::C);
	asEngine->RegisterEnumValue("Keyboard", "D", Keyboard::D);
	asEngine->RegisterEnumValue("Keyboard", "E", Keyboard::E);
	asEngine->RegisterEnumValue("Keyboard", "F", Keyboard::F);
	asEngine->RegisterEnumValue("Keyboard", "G", Keyboard::G);
	asEngine->RegisterEnumValue("Keyboard", "H", Keyboard::H);
	asEngine->RegisterEnumValue("Keyboard", "I", Keyboard::I);
	asEngine->RegisterEnumValue("Keyboard", "J", Keyboard::J);
	asEngine->RegisterEnumValue("Keyboard", "K", Keyboard::K);
	asEngine->RegisterEnumValue("Keyboard", "L", Keyboard::L);
	asEngine->RegisterEnumValue("Keyboard", "M", Keyboard::M);
	asEngine->RegisterEnumValue("Keyboard", "N", Keyboard::N);
	asEngine->RegisterEnumValue("Keyboard", "O", Keyboard::O);
	asEngine->RegisterEnumValue("Keyboard", "P", Keyboard::P);
	asEngine->RegisterEnumValue("Keyboard", "Q", Keyboard::Q);
	asEngine->RegisterEnumValue("Keyboard", "R", Keyboard::R);
	asEngine->RegisterEnumValue("Keyboard", "S", Keyboard::S);
	asEngine->RegisterEnumValue("Keyboard", "T", Keyboard::T);
	asEngine->RegisterEnumValue("Keyboard", "U", Keyboard::U);
	asEngine->RegisterEnumValue("Keyboard", "V", Keyboard::V);
	asEngine->RegisterEnumValue("Keyboard", "W", Keyboard::W);
	asEngine->RegisterEnumValue("Keyboard", "X", Keyboard::X);
	asEngine->RegisterEnumValue("Keyboard", "Y", Keyboard::Y);
	asEngine->RegisterEnumValue("Keyboard", "Z", Keyboard::Z);
	asEngine->RegisterEnumValue("Keyboard", "F1", Keyboard::F1);
	asEngine->RegisterEnumValue("Keyboard", "F2", Keyboard::F2);
	asEngine->RegisterEnumValue("Keyboard", "F3", Keyboard::F3);
	asEngine->RegisterEnumValue("Keyboard", "F4", Keyboard::F4);
	asEngine->RegisterEnumValue("Keyboard", "F5", Keyboard::F5);
	asEngine->RegisterEnumValue("Keyboard", "F6", Keyboard::F6);
	asEngine->RegisterEnumValue("Keyboard", "F7", Keyboard::F7);
	asEngine->RegisterEnumValue("Keyboard", "F8", Keyboard::F8);
	asEngine->RegisterEnumValue("Keyboard", "F9", Keyboard::F9);
	asEngine->RegisterEnumValue("Keyboard", "F10", Keyboard::F10);
	asEngine->RegisterEnumValue("Keyboard", "F11", Keyboard::F11);
	asEngine->RegisterEnumValue("Keyboard", "F12", Keyboard::F12);
	asEngine->RegisterEnumValue("Keyboard", "F13", Keyboard::F13);
	asEngine->RegisterEnumValue("Keyboard", "F14", Keyboard::F14);
	asEngine->RegisterEnumValue("Keyboard", "F15", Keyboard::F15);
	asEngine->RegisterEnumValue("Keyboard", "Escape", Keyboard::Escape);
	asEngine->RegisterEnumValue("Keyboard", "Back", Keyboard::Back);
	asEngine->RegisterEnumValue("Keyboard", "Add", Keyboard::Add);
	asEngine->RegisterEnumValue("Keyboard", "BackSlash", Keyboard::BackSlash);
	asEngine->RegisterEnumValue("Keyboard", "Comma", Keyboard::Comma);
	asEngine->RegisterEnumValue("Keyboard", "Dash", Keyboard::Dash);
	asEngine->RegisterEnumValue("Keyboard", "Delete", Keyboard::Delete);
	asEngine->RegisterEnumValue("Keyboard", "Divide", Keyboard::Divide);
	asEngine->RegisterEnumValue("Keyboard", "End", Keyboard::End);
	asEngine->RegisterEnumValue("Keyboard", "Equal", Keyboard::Equal);
	asEngine->RegisterEnumValue("Keyboard", "Home", Keyboard::Home);
	asEngine->RegisterEnumValue("Keyboard", "Insert", Keyboard::Insert);
	asEngine->RegisterEnumValue("Keyboard", "LAlt", Keyboard::LAlt);
	asEngine->RegisterEnumValue("Keyboard", "LBracket", Keyboard::LBracket);
	asEngine->RegisterEnumValue("Keyboard", "LControl", Keyboard::LControl);
	asEngine->RegisterEnumValue("Keyboard", "LShift", Keyboard::LShift);
	asEngine->RegisterEnumValue("Keyboard", "LSystem", Keyboard::LSystem);
	asEngine->RegisterEnumValue("Keyboard", "Menu", Keyboard::Menu);
	asEngine->RegisterEnumValue("Keyboard", "Multiply", Keyboard::Multiply);

	asEngine->RegisterEnumValue("Keyboard", "Num0", Keyboard::Num0);
	asEngine->RegisterEnumValue("Keyboard", "Num1", Keyboard::Num1);
	asEngine->RegisterEnumValue("Keyboard", "Num2", Keyboard::Num2);
	asEngine->RegisterEnumValue("Keyboard", "Num3", Keyboard::Num3);
	asEngine->RegisterEnumValue("Keyboard", "Num4", Keyboard::Num4);
	asEngine->RegisterEnumValue("Keyboard", "Num5", Keyboard::Num5);
	asEngine->RegisterEnumValue("Keyboard", "Num6", Keyboard::Num6);
	asEngine->RegisterEnumValue("Keyboard", "Num7", Keyboard::Num7);
	asEngine->RegisterEnumValue("Keyboard", "Num8", Keyboard::Num8);
	asEngine->RegisterEnumValue("Keyboard", "Num9", Keyboard::Num9);
	asEngine->RegisterEnumValue("Keyboard", "Numpad0", Keyboard::Numpad0);
	asEngine->RegisterEnumValue("Keyboard", "Numpad1", Keyboard::Numpad1);
	asEngine->RegisterEnumValue("Keyboard", "Numpad2", Keyboard::Numpad2);
	asEngine->RegisterEnumValue("Keyboard", "Numpad3", Keyboard::Numpad3);
	asEngine->RegisterEnumValue("Keyboard", "Numpad4", Keyboard::Numpad4);
	asEngine->RegisterEnumValue("Keyboard", "Numpad5", Keyboard::Numpad5);
	asEngine->RegisterEnumValue("Keyboard", "Numpad6", Keyboard::Numpad6);
	asEngine->RegisterEnumValue("Keyboard", "Numpad7", Keyboard::Numpad7);
	asEngine->RegisterEnumValue("Keyboard", "Numpad8", Keyboard::Numpad8);
	asEngine->RegisterEnumValue("Keyboard", "Numpad9", Keyboard::Numpad9);

	asEngine->RegisterEnumValue("Keyboard", "PageDown", Keyboard::PageDown);
	asEngine->RegisterEnumValue("Keyboard", "PageUp", Keyboard::PageUp);
	asEngine->RegisterEnumValue("Keyboard", "Period", Keyboard::Period);
	asEngine->RegisterEnumValue("Keyboard", "Pause", Keyboard::Pause);
	asEngine->RegisterEnumValue("Keyboard", "Space", Keyboard::Space);
	asEngine->RegisterEnumValue("Keyboard", "Quote", Keyboard::Quote);
	asEngine->RegisterEnumValue("Keyboard", "RAlt", Keyboard::RAlt);
	asEngine->RegisterEnumValue("Keyboard", "RControl", Keyboard::RControl);
	asEngine->RegisterEnumValue("Keyboard", "RShift", Keyboard::RShift);
	asEngine->RegisterEnumValue("Keyboard", "RBracket", Keyboard::RBracket);
	asEngine->RegisterEnumValue("Keyboard", "Return", Keyboard::Return);
	asEngine->RegisterEnumValue("Keyboard", "RSystem", Keyboard::RSystem);
	asEngine->RegisterEnumValue("Keyboard", "SemiColon", Keyboard::SemiColon);
	asEngine->RegisterEnumValue("Keyboard", "Slash", Keyboard::Slash);
	asEngine->RegisterEnumValue("Keyboard", "Subtract", Keyboard::Subtract);
	asEngine->RegisterEnumValue("Keyboard", "Tab", Keyboard::Tab);
	asEngine->RegisterEnumValue("Keyboard", "Tilde", Keyboard::Tilde);


	asEngine->RegisterEnumValue("Keyboard", "Down", Keyboard::Down);
	asEngine->RegisterEnumValue("Keyboard", "Left", Keyboard::Left);
	asEngine->RegisterEnumValue("Keyboard", "Right", Keyboard::Right);
	asEngine->RegisterEnumValue("Keyboard", "Up", Keyboard::Up);


	asEngine->RegisterEnum("Mouse");
	asEngine->RegisterEnumValue("Mouse", "Left", Mouse::Left);
	asEngine->RegisterEnumValue("Mouse", "Right", Mouse::Right);
	asEngine->RegisterEnumValue("Mouse", "Middle", Mouse::Middle);
	asEngine->RegisterEnumValue("Mouse", "XButton1", Mouse::XButton1);
	asEngine->RegisterEnumValue("Mouse", "XButton2", Mouse::XButton2);

	return true;
};

NEPHILIM_NS_END
