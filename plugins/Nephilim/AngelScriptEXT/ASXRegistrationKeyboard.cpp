#include <Nephilim/AngelScriptEXT/ASXRegistrationKeyboard.h>
#include <Nephilim/AngelScriptEXT/ASXEngine.h>
#include <Nephilim/Foundation/Event.h>

#include <angelscript.h>

NEPHILIM_NS_BEGIN

void registerKeyboardASX(ASXEngine& engine)
{
	engine.get()->RegisterEnum("Keyboard");
	engine.get()->RegisterEnumValue("Keyboard", "A", Keyboard::A);
	engine.get()->RegisterEnumValue("Keyboard", "B", Keyboard::B);
	engine.get()->RegisterEnumValue("Keyboard", "C", Keyboard::C);
	engine.get()->RegisterEnumValue("Keyboard", "D", Keyboard::D);
	engine.get()->RegisterEnumValue("Keyboard", "E", Keyboard::E);
	engine.get()->RegisterEnumValue("Keyboard", "F", Keyboard::F);
	engine.get()->RegisterEnumValue("Keyboard", "G", Keyboard::G);
	engine.get()->RegisterEnumValue("Keyboard", "H", Keyboard::H);
	engine.get()->RegisterEnumValue("Keyboard", "I", Keyboard::I);
	engine.get()->RegisterEnumValue("Keyboard", "J", Keyboard::J);
	engine.get()->RegisterEnumValue("Keyboard", "K", Keyboard::K);
	engine.get()->RegisterEnumValue("Keyboard", "L", Keyboard::L);
	engine.get()->RegisterEnumValue("Keyboard", "M", Keyboard::M);
	engine.get()->RegisterEnumValue("Keyboard", "N", Keyboard::N);
	engine.get()->RegisterEnumValue("Keyboard", "O", Keyboard::O);
	engine.get()->RegisterEnumValue("Keyboard", "P", Keyboard::P);
	engine.get()->RegisterEnumValue("Keyboard", "Q", Keyboard::Q);
	engine.get()->RegisterEnumValue("Keyboard", "R", Keyboard::R);
	engine.get()->RegisterEnumValue("Keyboard", "S", Keyboard::S);
	engine.get()->RegisterEnumValue("Keyboard", "T", Keyboard::T);
	engine.get()->RegisterEnumValue("Keyboard", "U", Keyboard::U);
	engine.get()->RegisterEnumValue("Keyboard", "V", Keyboard::V);
	engine.get()->RegisterEnumValue("Keyboard", "W", Keyboard::W);
	engine.get()->RegisterEnumValue("Keyboard", "X", Keyboard::X);
	engine.get()->RegisterEnumValue("Keyboard", "Y", Keyboard::Y);
	engine.get()->RegisterEnumValue("Keyboard", "Z", Keyboard::Z);
	engine.get()->RegisterEnumValue("Keyboard", "F1", Keyboard::F1);
	engine.get()->RegisterEnumValue("Keyboard", "F2", Keyboard::F2);
	engine.get()->RegisterEnumValue("Keyboard", "F3", Keyboard::F3);
	engine.get()->RegisterEnumValue("Keyboard", "F4", Keyboard::F4);
	engine.get()->RegisterEnumValue("Keyboard", "F5", Keyboard::F5);
	engine.get()->RegisterEnumValue("Keyboard", "F6", Keyboard::F6);
	engine.get()->RegisterEnumValue("Keyboard", "F7", Keyboard::F7);
	engine.get()->RegisterEnumValue("Keyboard", "F8", Keyboard::F8);
	engine.get()->RegisterEnumValue("Keyboard", "F9", Keyboard::F9);
	engine.get()->RegisterEnumValue("Keyboard", "F10", Keyboard::F10);
	engine.get()->RegisterEnumValue("Keyboard", "F11", Keyboard::F11);
	engine.get()->RegisterEnumValue("Keyboard", "F12", Keyboard::F12);
	engine.get()->RegisterEnumValue("Keyboard", "F13", Keyboard::F13);
	engine.get()->RegisterEnumValue("Keyboard", "F14", Keyboard::F14);
	engine.get()->RegisterEnumValue("Keyboard", "F15", Keyboard::F15);
	engine.get()->RegisterEnumValue("Keyboard", "Escape", Keyboard::Escape);
	engine.get()->RegisterEnumValue("Keyboard", "Back", Keyboard::Back);
	engine.get()->RegisterEnumValue("Keyboard", "Add", Keyboard::Add);
	engine.get()->RegisterEnumValue("Keyboard", "BackSlash", Keyboard::BackSlash);
	engine.get()->RegisterEnumValue("Keyboard", "Comma", Keyboard::Comma);
	engine.get()->RegisterEnumValue("Keyboard", "Dash", Keyboard::Dash);
	engine.get()->RegisterEnumValue("Keyboard", "Delete", Keyboard::Delete);
	engine.get()->RegisterEnumValue("Keyboard", "Divide", Keyboard::Divide);
	engine.get()->RegisterEnumValue("Keyboard", "End", Keyboard::End);
	engine.get()->RegisterEnumValue("Keyboard", "Equal", Keyboard::Equal);
	engine.get()->RegisterEnumValue("Keyboard", "Home", Keyboard::Home);
	engine.get()->RegisterEnumValue("Keyboard", "Insert", Keyboard::Insert);
	engine.get()->RegisterEnumValue("Keyboard", "LAlt", Keyboard::LAlt);
	engine.get()->RegisterEnumValue("Keyboard", "LBracket", Keyboard::LBracket);
	engine.get()->RegisterEnumValue("Keyboard", "LControl", Keyboard::LControl);
	engine.get()->RegisterEnumValue("Keyboard", "LShift", Keyboard::LShift);
	engine.get()->RegisterEnumValue("Keyboard", "LSystem", Keyboard::LSystem);
	engine.get()->RegisterEnumValue("Keyboard", "Menu", Keyboard::Menu);
	engine.get()->RegisterEnumValue("Keyboard", "Multiply", Keyboard::Multiply);

	engine.get()->RegisterEnumValue("Keyboard", "Num0", Keyboard::Num0);
	engine.get()->RegisterEnumValue("Keyboard", "Num1", Keyboard::Num1);
	engine.get()->RegisterEnumValue("Keyboard", "Num2", Keyboard::Num2);
	engine.get()->RegisterEnumValue("Keyboard", "Num3", Keyboard::Num3);
	engine.get()->RegisterEnumValue("Keyboard", "Num4", Keyboard::Num4);
	engine.get()->RegisterEnumValue("Keyboard", "Num5", Keyboard::Num5);
	engine.get()->RegisterEnumValue("Keyboard", "Num6", Keyboard::Num6);
	engine.get()->RegisterEnumValue("Keyboard", "Num7", Keyboard::Num7);
	engine.get()->RegisterEnumValue("Keyboard", "Num8", Keyboard::Num8);
	engine.get()->RegisterEnumValue("Keyboard", "Num9", Keyboard::Num9);
	engine.get()->RegisterEnumValue("Keyboard", "Numpad0", Keyboard::Numpad0);
	engine.get()->RegisterEnumValue("Keyboard", "Numpad1", Keyboard::Numpad1);
	engine.get()->RegisterEnumValue("Keyboard", "Numpad2", Keyboard::Numpad2);
	engine.get()->RegisterEnumValue("Keyboard", "Numpad3", Keyboard::Numpad3);
	engine.get()->RegisterEnumValue("Keyboard", "Numpad4", Keyboard::Numpad4);
	engine.get()->RegisterEnumValue("Keyboard", "Numpad5", Keyboard::Numpad5);
	engine.get()->RegisterEnumValue("Keyboard", "Numpad6", Keyboard::Numpad6);
	engine.get()->RegisterEnumValue("Keyboard", "Numpad7", Keyboard::Numpad7);
	engine.get()->RegisterEnumValue("Keyboard", "Numpad8", Keyboard::Numpad8);
	engine.get()->RegisterEnumValue("Keyboard", "Numpad9", Keyboard::Numpad9);

	engine.get()->RegisterEnumValue("Keyboard", "PageDown", Keyboard::PageDown);
	engine.get()->RegisterEnumValue("Keyboard", "PageUp", Keyboard::PageUp);
	engine.get()->RegisterEnumValue("Keyboard", "Period", Keyboard::Period);
	engine.get()->RegisterEnumValue("Keyboard", "Pause", Keyboard::Pause);
	engine.get()->RegisterEnumValue("Keyboard", "Space", Keyboard::Space);
	engine.get()->RegisterEnumValue("Keyboard", "Quote", Keyboard::Quote);
	engine.get()->RegisterEnumValue("Keyboard", "RAlt", Keyboard::RAlt);
	engine.get()->RegisterEnumValue("Keyboard", "RControl", Keyboard::RControl);
	engine.get()->RegisterEnumValue("Keyboard", "RShift", Keyboard::RShift);
	engine.get()->RegisterEnumValue("Keyboard", "RBracket", Keyboard::RBracket);
	engine.get()->RegisterEnumValue("Keyboard", "Return", Keyboard::Return);
	engine.get()->RegisterEnumValue("Keyboard", "RSystem", Keyboard::RSystem);
	engine.get()->RegisterEnumValue("Keyboard", "SemiColon", Keyboard::SemiColon);
	engine.get()->RegisterEnumValue("Keyboard", "Slash", Keyboard::Slash);
	engine.get()->RegisterEnumValue("Keyboard", "Subtract", Keyboard::Subtract);
	engine.get()->RegisterEnumValue("Keyboard", "Tab", Keyboard::Tab);
	engine.get()->RegisterEnumValue("Keyboard", "Tilde", Keyboard::Tilde);


	engine.get()->RegisterEnumValue("Keyboard", "Down", Keyboard::Down);
	engine.get()->RegisterEnumValue("Keyboard", "Left", Keyboard::Left);
	engine.get()->RegisterEnumValue("Keyboard", "Right", Keyboard::Right);
	engine.get()->RegisterEnumValue("Keyboard", "Up", Keyboard::Up);
}

NEPHILIM_NS_END