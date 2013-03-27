#include <Nephilim/UILineEdit.h>
#include <Nephilim/ASEngine.h>

#include "AS/aswrappedcall.h"

#include <iostream>
using namespace std;


PARABOLA_NAMESPACE_BEGIN

UIControl* UILineEditRefCast(UILineEdit* a) 
{
	return refCast<UILineEdit, UIControl>(a);
}

static UILineEdit* customInstancer()
{
	return new UILineEdit();
}

void Wrap_UILineEdit_factory(asIScriptGeneric *gen)
{
	*reinterpret_cast<UILineEdit**>(gen->GetAddressOfReturnLocation()) = new UILineEdit();
}

void Wrap_UILineEdit_addReference(asIScriptGeneric *gen)
{
	reinterpret_cast<UILineEdit*>(gen->GetObject())->addReference();
}


void Wrap_UILineEdit_removeReference(asIScriptGeneric *gen)
{
	reinterpret_cast<UILineEdit*>(gen->GetObject())->removeReference();
}

/// Register the buttons
bool registerUILineEdit(ASEngine* engine)
{
	engine->getASEngine()->RegisterObjectType("UILineEdit", sizeof(UILineEdit), asOBJ_REF);

	if(engine->getPortableMode())
	{
		engine->getASEngine()->RegisterObjectBehaviour("UILineEdit", asBEHAVE_FACTORY, "UILineEdit@ f()", asFUNCTION(Wrap_UILineEdit_factory), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("UILineEdit", asBEHAVE_ADDREF, "void f()",  asFUNCTION(Wrap_UILineEdit_addReference), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("UILineEdit", asBEHAVE_RELEASE, "void f()",  asFUNCTION(Wrap_UILineEdit_removeReference), asCALL_GENERIC);
		//engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_FACTORY, "UIButton@ f()", WRAP_FN(customInstancer), asCALL_GENERIC);
		//engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_ADDREF, "void f()", WRAP_MFN(UIButton, addReference), asCALL_GENERIC);
		//engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_RELEASE, "void f()", WRAP_MFN(UIButton, removeReference), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("UILineEdit", asBEHAVE_IMPLICIT_REF_CAST, "UIControl@ f()", WRAP_OBJ_LAST(UILineEditRefCast), asCALL_GENERIC);

		engine->getASEngine()->RegisterObjectMethod("UILineEdit", "void bindSignal(const string &in, Slot@)", WRAP_MFN(UILineEdit, bindSignal), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("UILineEdit", "void setPosition(float,float)", WRAP_MFN(UILineEdit, setPosition), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("UILineEdit", "void setSize(float,float)", WRAP_MFN(UILineEdit, setSize), asCALL_GENERIC);
		//engine->getASEngine()->RegisterObjectMethod("UILineEdit", "void setProperty(const string &in, const string &in)", WRAP_MFN(UIButton, setRawProperty), asCALL_GENERIC);

	}
	else 
	{
		engine->getASEngine()->RegisterObjectBehaviour("UILineEdit", asBEHAVE_FACTORY, "UILineEdit@ f()", asFUNCTION(genericFactory<UILineEdit>), asCALL_CDECL);
		engine->getASEngine()->RegisterObjectBehaviour("UILineEdit", asBEHAVE_ADDREF, "void f()", asMETHOD(UILineEdit, addReference), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectBehaviour("UILineEdit", asBEHAVE_RELEASE, "void f()", asMETHOD(UILineEdit, removeReference), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectBehaviour("UILineEdit", asBEHAVE_IMPLICIT_REF_CAST, "UIControl@ f()", asFUNCTION((refCast<UILineEdit,UIControl>)), asCALL_CDECL_OBJLAST);

		engine->getASEngine()->RegisterObjectMethod("UILineEdit", "void bindSignal(const string &in, Slot@)", asMETHOD(UILineEdit, bindSignal), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("UILineEdit", "void setPosition(float,float)", asMETHOD(UILineEdit, setPosition), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("UILineEdit", "void setSize(float,float)", asMETHOD(UILineEdit, setSize), asCALL_THISCALL);
		//engine->getASEngine()->RegisterObjectMethod("UILineEdit", "void setProperty(const string &in, const string &in)", asMETHOD(UIButton, setRawProperty), asCALL_THISCALL);

	}
	return true;
}
UILineEdit::UILineEdit() : UIControl(), m_pipeIndex(0)
{

}


bool UILineEdit::onEventNotification(Event& event){
	/*if(event.type == Event::TextEntered){
		s += event.text.unicode;
		t.setString(s);
	}*/
	return true;
};

bool UILineEdit::onKeyPressed(Keyboard::Key key)
{
	if(key == Keyboard::Left)
	{
		m_pipeIndex--;
	}
	else if(key == Keyboard::Right)
	{
		m_pipeIndex++;
	}
	else if(key == Keyboard::Back)
	{
		eraseCharacter();
	}
	else if(key == Keyboard::Delete)
	{
		m_pipeIndex++;
		eraseCharacter();
	}

	return false;
}

bool UILineEdit::onTextEvent(Uint32 code)
{
	if(code >= 32)
	{
		addCharacter(code);
		return true;
	}
	else return false;
}


void UILineEdit::addCharacter(Uint32 charCode)
{
	s.insert(s.begin() + m_pipeIndex, charCode);
	m_pipeIndex++;
}

void UILineEdit::eraseCharacter()
{
	s.erase(s.begin() + m_pipeIndex - 1);
	m_pipeIndex--;
}

void UILineEdit::setText(const String& text){
	s = text;
	t.setString(s);
};


void UILineEdit::draw(Renderer* renderer){
	t.setString(s);
	t.setPosition(m_bounds.left,m_bounds.top);
	t.setCharacterSize(15);
	if(m_hasFocus)
	{
		t.setColor(Color::Red);
	}
	else
	{
		t.setColor(Color::White);
	}
	
	// The pipe
	float pipePosition = t.getCharacterPosition(m_pipeIndex).x + 1;
	renderer->draw(t);
	renderer->drawDebugLine(Vec2f(m_bounds.left + pipePosition, m_bounds.top), Vec2f(m_bounds.left + pipePosition, m_bounds.top + t.getCharacterSize()), Color::Red);

	//renderer->drawDebugLine(Vec2f(0,0), Vec2f(400,400), Color::White);
};


PARABOLA_NAMESPACE_END