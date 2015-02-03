#include <Nephilim/UI/UIComponentText.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Foundation/StringList.h>
#include <Nephilim/Foundation/Math.h>
NEPHILIM_NS_BEGIN

UIComponentText::UIComponentText()
: m_string("unset")
, m_horizontal(Center)
, m_vertical(Center)
{
	component_id = UIComponent::TextComponent;
	color = Color(151,151,151);
}


UIComponentText::UIComponentText(const String& text, Alignment horizontal, Alignment vertical)
: m_string(text)
, m_horizontal(horizontal)
, m_vertical(vertical)
{
	component_id = UIComponent::TextComponent;
	color = Color(211,211,211);
}

void UIComponentText::onAttach(UIView* view)
{	
	text.setCharacterSize(14);
	text.setString(m_string);
	text.setColor(color);
	text.setOrigin(0.f, 0.f);
	text.setPosition(view->getPosition());

	if(m_horizontal == Center)
	{
		text.setPosition(view->getPosition().x + view->getSize().x / 2.f, text.getPosition().y);
		text.setOrigin(text.getLocalBounds().width / 2.f, 0.f);
	}
}

void UIComponentText::onPropertySet(const StringList& targetObject, const String& value)
{
	if(targetObject.size() == 2 && targetObject[0] == "text" && targetObject[1] == "caption")
	{
		m_string = value;
	}
	if(targetObject.size() == 2 && targetObject[0] == "text" && targetObject[1] == "color")
	{
		if(value == "red")
		{
			color = Color::Red;
		}
		if(value == "blue")
		{
			color = Color::Blue;
		}
		if(value == "white")
		{
			color = Color::White;
		}
	}
}


void UIComponentText::onRender(GraphicsDevice* renderer, UIView* view, const mat4& parentTransform)
{
	text.setCharacterSize(12);
	text.setString(m_string);
	text.setColor(color);
	text.setOrigin(0.f, 0.f);
	text.setPosition(view->getPosition().x + mParent->mPadding.left, view->getPosition().y);

	if(m_horizontal == Center)
	{
		text.setPosition(view->getSize().x / 2.f, text.getPosition().y);
		text.setOrigin(text.getLocalBounds().width / 2.f, 0.f);
	}

	if(m_vertical == Center)
	{
		text.setPosition(text.getPosition().x, view->getSize().y / 2.f);
		text.setOrigin(text.getOrigin().x, text.getLocalBounds().height / 2.f);
	}

	text.setFont(*view->getCore()->m_defaultFont);
	text.setOrigin(static_cast<int>(text.getOrigin().x + 0.5f), static_cast<int>(text.getOrigin().y + 0.5f));
	text.setPosition(static_cast<int>(text.getPosition().x + 0.5f), static_cast<int>(text.getPosition().y + 0.5f));
	
	mat4 localTransform = mat4::translate(vec3(0.f, 20.f, 1.f)) * mat4::rotatex(math::pi);

	renderer->setModelMatrix(parentTransform * text.getTransform().getMatrix());
	renderer->draw(text);
}

NEPHILIM_NS_END