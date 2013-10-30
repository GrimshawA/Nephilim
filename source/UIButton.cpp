#include <Nephilim/UIButton.h>
#include <Nephilim/Text.h>
#include <Nephilim/RectangleShape.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN


UIButton::UIButton()
: UIControl()
, m_color(0,0,0)
, hover(false)
, m_normalTexture(NULL)
{
	setSize(200,40);
	m_label = "unassigned";

	buttonLabel.setColor(Color::White);
}

UIButton::~UIButton()
{
}

UIButton::UIButton(const String& title)
: UIControl()
, m_color(0,0,0)
, m_label(title)
, hover(false)
, m_normalTexture(NULL)
{
	UIPropertyMap& hoverproperties = m_styleInfo["hover"];
	hoverproperties["color"] = UIProperty(Color::Blue);

	UIPropertyMap& normalproperties = m_styleInfo["normal"];
	normalproperties["color"] = UIProperty(Color::Orange);

}

void UIButton::setNormalTexture(const String& filename)
{
	
}

void UIButton::setHoverTexture(const String& filename)
{
	
}

bool UIButton::onEventNotification(Event& event)
{
	

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

/// Sets the label of the button
void UIButton::setLabel(const String& text)
{
	m_label = text;
	m_baseLabel = m_label;
}

String UIButton::getLabel()
{
	return m_label;
}

void UIButton::draw(Renderer* renderer)
{
	if(!m_stateContext->m_defaultFont.isLoaded())
	{
		Log("UI: There is no default font for showing text.");
	}

	RectangleShape background;
	background.setPosition(getPosition());
	background.setSize(getSize());
	if(m_classInfo["hover"])
	{
		background.setColor(m_styleInfo["hover"]["color"].getColor());
	}
	else
	{
		background.setColor(m_styleInfo["normal"]["color"].getColor());
	}
	if(m_normalTexture)
	{
		background.setTexture(m_normalTexture);
	}

	renderer->draw(background);
	
    // -- Label
	buttonLabel.setFont(m_stateContext->m_defaultFont);
	buttonLabel.setString(m_label);
	buttonLabel.setCharacterSize(m_bounds.height / 2);
	buttonLabel.setOrigin(static_cast<int>((buttonLabel.getLocalBounds().width / 2.f ) + 0.5f), static_cast<int>((buttonLabel.getLocalBounds().height / 2.f) + 0.5f));
	buttonLabel.setPosition(static_cast<int>((m_bounds.left + m_bounds.width / 2.f ) + 0.5f), static_cast<int>((m_bounds.top +  m_bounds.height / 2.f) + 0.5f));
	renderer->draw(buttonLabel);
};

NEPHILIM_NS_END
