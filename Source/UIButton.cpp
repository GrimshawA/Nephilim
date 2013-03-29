#include <Nephilim/UIButton.h>
#include <Nephilim/Text.h>

#include <Nephilim/ASEngine.h>
#include <Nephilim/ASSlot.h>
#include "AS/aswrappedcall.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

UIControl* UIButtonRefCast(UIButton* a) 
{
	return refCast<UIButton, UIControl>(a);
}

static UIButton* customInstancer()
{
	return new UIButton();
}

void Wrap_UIButton_factory(asIScriptGeneric *gen)
{
	*reinterpret_cast<UIButton**>(gen->GetAddressOfReturnLocation()) = new UIButton();
}

void Wrap_UIButton_addReference(asIScriptGeneric *gen)
{
	reinterpret_cast<UIButton*>(gen->GetObject())->addReference();
}


void Wrap_UIButton_removeReference(asIScriptGeneric *gen)
{
	reinterpret_cast<UIButton*>(gen->GetObject())->removeReference();
}

/// Register the buttons
bool registerUIButton(ASEngine* engine)
{
	engine->getASEngine()->RegisterObjectType("UIButton", sizeof(UIButton), asOBJ_REF);

	if(engine->getPortableMode())
	{
		engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_FACTORY, "UIButton@ f()", asFUNCTION(Wrap_UIButton_factory), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_ADDREF, "void f()",  asFUNCTION(Wrap_UIButton_addReference), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_RELEASE, "void f()",  asFUNCTION(Wrap_UIButton_removeReference), asCALL_GENERIC);
		//engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_FACTORY, "UIButton@ f()", WRAP_FN(customInstancer), asCALL_GENERIC);
		//engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_ADDREF, "void f()", WRAP_MFN(UIButton, addReference), asCALL_GENERIC);
		//engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_RELEASE, "void f()", WRAP_MFN(UIButton, removeReference), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_IMPLICIT_REF_CAST, "UIControl@ f()", WRAP_OBJ_LAST(UIButtonRefCast), asCALL_GENERIC);

 		engine->getASEngine()->RegisterObjectMethod("UIButton", "void setLabel(const string &in)", WRAP_MFN(UIButton, setLabel), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("UIButton", "void setProperty(const string &in, const string &in)", WRAP_MFN(UIButton, setRawProperty), asCALL_GENERIC);
	
	}
	else 
	{
		engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_FACTORY, "UIButton@ f()", asFUNCTION(genericFactory<UIButton>), asCALL_CDECL);
		engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_ADDREF, "void f()", asMETHOD(UIButton, addReference), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_RELEASE, "void f()", asMETHOD(UIButton, removeReference), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectBehaviour("UIButton", asBEHAVE_IMPLICIT_REF_CAST, "UIControl@ f()", asFUNCTION((refCast<UIButton,UIControl>)), asCALL_CDECL_OBJLAST);
		
		engine->getASEngine()->RegisterObjectMethod("UIButton", "void setLabel(const string &in)", asMETHOD(UIButton, setLabel), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("UIButton", "void setProperty(const string &in, const string &in)", asMETHOD(UIButton, setRawProperty), asCALL_THISCALL);

	}

	registerUIControlSubtype("UIButton", engine);

	return true;
}

/// Constructs the button
UIButton::UIButton() :  m_color(0,0,0) , hover(false){
	setSize(200,40);
	m_label = "unassigned";
	//TESTLOG("UIBUTTON BORN\n")
		UIControl();
		//PRINTLOG("f", "REF COUNT: %d\n", refCount);
	//cout<<"me: "<<this<<endl;
};

UIButton::~UIButton()
{
	//TESTLOG("UIBUTTON KILLED\n")
}


/// Constructs the button from a label text
UIButton::UIButton(const String& title) : UIControl(), m_color(0,0,0), m_label(title), hover(false){

};

/// Callback to handle an event
bool UIButton::onEventNotification(Event& event){
	if(event.type == Event::MouseButtonPressed){
		if(m_bounds.contains(event.mouseButton.x, event.mouseButton.y)){
			// drag test
			if(getContext())
			{
				getContext()->m_dragControl = this->clone();
				getContext()->m_dragOffset = Vec2f(event.mouseButton.x - m_bounds.left, event.mouseButton.y - m_bounds.top);
			}
		}

		
	}
	if(event.type == Event::TouchPressed){
		if(m_bounds.contains(event.x, event.y)){
			// drag test
			if(getContext())
			{
				getContext()->m_dragControl = this->clone();
				getContext()->m_dragOffset = Vec2f(event.x - m_bounds.left, event.y - m_bounds.top);
			}
		}
	}

	if(event.type == Event::MouseButtonReleased){
		if(m_bounds.contains(event.mouseButton.x, event.mouseButton.y)){
			onClick();
		}

		// drag test
		if(getContext())
		{
			getContext()->m_dragControl = NULL;
		}
	}

	if(event.type == Event::TouchReleased){
		if(m_bounds.contains(event.x, event.y)){
			onClick();
		}

		// drag test
		if(getContext())
		{
			getContext()->m_dragControl = NULL;
		}
	}

	if(event.type == Event::MouseMoved)
	{
		if(m_bounds.contains(event.mouseMove.x, event.mouseMove.y)){
			setProperty<Color>("background-color", Color::White);
		}
		else
		{
			setProperty<Color>("background-color", Color(91,91,91));
		}
	}

	if(event.type == Event::TouchMoved)
	{
		if(m_bounds.contains(event.x, event.y)){	
			setProperty<Color>("background-color", Color::White);
		}
		else
		{
			setProperty<Color>("background-color", Color(91,91,91));
		}
	}
	return true;
}

UIControl* UIButton::clone()
{
	return new UIButton(*this);
};

void UIButton::innerLanguageSwitch()
{
	String res =  m_stateContext->m_localization.getString(m_baseLabel);
	if(!res.empty())m_label = res;
}

void UIButton::setRawProperty(const String& name, const String& val)
{
	if(name == "background-image")
	{
		cout<<"[UIButton] Assigning image"<<endl;
	}
}


void UIButton::bindSignal(const String &signalName, ASSlot* slot )
{
	UIControl::bindSignal(signalName, slot);

	if(!slot){
		cout<<"INVALID SLOT"<<endl;
		return;
	}

	//cout<<"Binding slot: "<<slot<<endl;




}

/// Sets the label of the button
void UIButton::setLabel(const String& text)
{
	m_label = text;
	m_baseLabel = m_label;
};


/// Callback to render itself, renders children
void UIButton::draw(Renderer* renderer){
	Text t;
	t.setFont(m_stateContext->m_defaultFont);
	t.setString(m_label);
	t.setColor(m_color);
	t.setCharacterSize(19);
	t.setOrigin(t.getLocalBounds().width/2, t.getLocalBounds().height/2);
	t.setPosition(m_bounds.left + m_bounds.width/2, m_bounds.top +  m_bounds.height/2);
	renderer->draw(t);
};

NEPHILIM_NS_END
