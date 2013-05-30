#include <Nephilim/UIButton.h>
#include <Nephilim/Text.h>
#include <Nephilim/RectangleShape.h>

#include <Nephilim/ASEngine.h>
#include <Nephilim/ASSlot.h>
#include "AS/aswrappedcall.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

UIButton::UIButton()
: UIControl()
, m_color(0,0,0)
, hover(false)
{
	setSize(200,40);
	m_label = "unassigned";
};

UIButton::~UIButton()
{

}


/// Constructs the button from a label text
UIButton::UIButton(const String& title) : UIControl(), m_color(0,0,0), m_label(title), hover(false){

};

void UIButton::setNormalTexture(const String& filename)
{
	m_normal.loadFromFile(filename);
}

void UIButton::setHoverTexture(const String& filename)
{
	m_hovert.loadFromFile(filename);
}

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
		if(m_bounds.contains(event.touch.x, event.touch.y)){
			// drag test
			if(getContext())
			{
				getContext()->m_dragControl = this->clone();
				getContext()->m_dragOffset = Vec2f(event.touch.x - m_bounds.left, event.touch.y - m_bounds.top);
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
		if(m_bounds.contains(event.touch.x, event.touch.y)){
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
		if(m_bounds.contains(event.touch.x, event.touch.y)){	
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

void UIButton::draw(Renderer* renderer)
{
	if(!m_stateContext->m_defaultFont.isLoaded())
	{
		Log("UI: There is no default font for showing text.");
	}

	

	RectangleShape background;
	if(!m_hovered)
		background.setTexture(&m_normal);
	else
	{
		background.setTexture(&m_hovert);
	}

	background.setPosition(m_bounds.left, m_bounds.top);
	background.setSize(m_bounds.width, m_bounds.height);
	background.setColor(Color::White);
	renderer->draw(background);

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
