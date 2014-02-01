#include <Nephilim/UI/UIComponentImage.h>
#include <Nephilim/UIView.h>

NEPHILIM_NS_BEGIN

UIComponentText::UIComponentText()
: m_string("")
, m_horizontal(Center)
, m_vertical(Center)
{
	component_id = UIViewComponent::TextComponent;
}


UIComponentText::UIComponentText(const String& text, Alignment horizontal, Alignment vertical)
: m_string(text)
, m_horizontal(horizontal)
, m_vertical(vertical)
{
	component_id = UIViewComponent::TextComponent;
}

void UIComponentText::onAttach(UIView* view)
{
	
	text.setCharacterSize(14);
	text.setString(m_string);
	text.setColor(Color(151,151,151));
	text.setOrigin(0.f, 0.f);
	text.setPosition(view->getPosition());

	Log("sdfasf");
	if(m_horizontal == Center)
	{
		text.setPosition(view->getPosition().x + view->getSize().x / 2.f, text.getPosition().y);
		text.setOrigin(text.getLocalBounds().width / 2.f, 0.f);
	}
}

void UIComponentText::onRender(Renderer* renderer, UIView* view)
{

	text.setCharacterSize(14);
	text.setString(m_string);
	text.setColor(Color(151,151,151));
	text.setOrigin(0.f, 0.f);
	text.setPosition(view->getPosition());

	if(m_horizontal == Center)
	{
		text.setPosition(view->getPosition().x + view->getSize().x / 2.f, text.getPosition().y);
		text.setOrigin(text.getLocalBounds().width / 2.f, 0.f);
	}

	if(m_vertical == Center)
	{
		text.setPosition(text.getPosition().x, view->getPosition().y + view->getSize().y / 2.f);
		text.setOrigin(text.getOrigin().x, text.getLocalBounds().height / 2.f);
	}

	text.setFont(*view->getContext()->m_defaultFont);
	renderer->draw(text);
}

NEPHILIM_NS_END